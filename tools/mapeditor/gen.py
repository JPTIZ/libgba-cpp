import json

from os.path import abspath, basename, splitext

from jinja2 import Environment, FileSystemLoader

from mapeditor.map import Map, Tileset


def export(data,
           output='output',
           template='template',
           namespace='resources',
           exts=('h', 'cpp')):
    def render(f, template, env, data):
        MAP_SIZES = {
            (32, 32): 'gba::graphics::MapSize::TEXT_256X256',
        }
        tileset, _ = splitext(basename(data.tileset.filename)
                              .replace('-', '_'))

        template = env.get_template(template)
        f.write(template.render(
            name=data.name.lower(),
            namespace=namespace.lower(),
            layers=data.layers,
            tileset=tileset,
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


def save(map, filename='map'):
    print(f'saving {filename}...')
    with open(filename, 'w') as f:
        data = {
                'name': map.name,
                'size': map.size,
                'tile_size': map.tile_size,
                'tileset': map.tileset.filename,
                'layers': [layer.data for layer in map.layers]
               }

        json.dump(data, f)


def load(filename):
    print(f'opening {filename}...')
    with open(filename, 'r') as f:
        data = json.load(f)
        map = Map(data['name'],
                  Tileset(data['tileset']),
                  size=data['size'],
                  tile_size=data['tile_size'],
                  layers=len(data['layers']))
        for map_layer, layer in zip(map.layers, data['layers']):
            map_layer.data = layer
        map.remake_image()
        return map


def chunks(x, n):
    it = iter(x)
    while True:
        t = tuple(next(it) for _ in range(n))
        if len(t) != n:
            return
        yield t
