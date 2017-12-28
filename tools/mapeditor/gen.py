from random import randint
from os.path import abspath

from jinja2 import Environment, FileSystemLoader


def export(data,
           output='output',
           template='template',
           namespace='resources',
           exts=('h', 'cpp')):
    def render(f, template, env, data):
        MAP_SIZES = {
            (32, 32): 'gba::graphics::MapSize::TEXT_256X256',
        }
        size = data.size
        data.tilemap = [randint(0, 100) for _ in range(size[0] * size[1])]

        template = env.get_template(template)
        f.write(template.render(
            name=data.name.lower(),
            namespace=namespace.lower(),
            layers=data.layers,
            tilemap=data.tilemap,
            tileset=data.tileset.filename,
            map_size=MAP_SIZES[data.size]))

    env = Environment(
                    trim_blocks=True,
                    autoescape=False,
                    loader=FileSystemLoader(abspath('.'))
                )
    env.filters['chunks'] = chunks
    for ext in exts:
        print(f'exporting to {output}.{ext} (based on {template}.{ext})')
        with open(f'{output}.{ext}', 'w') as f:
            render(f, f'mapeditor/{template}.{ext}', env, data)


def chunks(x, n):
    it = iter(x)
    while True:
        t = tuple(next(it) for _ in range(n))
        if len(t) != n:
            return
        yield t
