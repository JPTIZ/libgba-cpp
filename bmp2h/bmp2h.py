#!/usr/bin/env python3
from os.path import abspath
from typing import NamedTuple, List

from carl import command
from jinja2 import Environment, FileSystemLoader
from PIL import Image


class Color(NamedTuple):
    r: int
    g: int
    b: int


class MapData(NamedTuple):
    name: str
    namespace: str
    colors: List[Color]
    tiles: List[List[List[int]]]


def chunks(x, n):
    it = iter(x)
    while True:
        t = tuple(next(it) for _ in range(n))
        if len(t) != n:
            return
        yield t


def render(f, template, env, data):
    template = env.get_template(template)
    f.write(template.render(
        namespace=data.namespace,
        name=data.name,
        n_colors=len(data.colors),
        n_tiles=len(data.tiles),
        colors=data.colors,
        tiles=data.tiles))


def export(data, template='template'):
    env = Environment(
                    block_start_string='$block{',
                    block_end_string='}',
                    variable_start_string='${',
                    variable_end_string='}',
                    comment_start_string='\#{',
                    comment_end_string='}',
                    line_statement_prefix='%%',
                    line_comment_prefix='%#',
                    trim_blocks=True,
                    autoescape=False,
                    loader=FileSystemLoader(abspath('.'))
                )
    env.filters['chunks'] = chunks
    with open(f'{data.name}.h', 'w') as f:
        render(f, f'{template}.h', env, data)
    with open(f'{data.name}.cpp', 'w') as f:
        render(f, f'{template}.cpp', env, data)


def extract_colors(palette):
    return list(filter(lambda c: c != Color(0, 0, 0),
                       [Color(r // 8,
                              g // 8,
                              b // 8)
                        for r, g, b in chunks(palette, 3)]))[:256]


def extract_tiles(image, pixels):
    tiles = []
    # for each 8x8 block
    for block_y in range(0, image.height, 8):
        for block_x in range(0, image.width, 8):
            tile = []
            # for each 8x1 row in block
            for y in range(block_y, block_y + 8):
                # for each pixel in row
                row = []
                # first integer
                for x in range(block_x, block_x + 4):
                    row.append(pixels[x, y] + 1)
                tile.append(row)
                row = []
                # second integer
                for x in range(block_x + 4, block_x + 8):
                    row.append(pixels[x, y] + 1)
                tile.append(row)
            tiles.append(tile)
    return [[sum(v << (i * 8) for i, v in enumerate(row))
             for row in tile] for tile in tiles]


@command
def main(bitmap: 'Bitmap file to be read.',
         template: 'Template header file.' = 'template',
         namespace: 'Main namespace to place data.' = 'resources',
         name: 'Tileset name. Will be used for variable naming.' = 'sample'):

    image = Image.open(bitmap).convert(
                mode='P',
                palette=Image.ADAPTIVE,
                colors=255)

    colors = extract_colors(image.palette.palette)
    tiles = extract_tiles(image, image.load())

    data = MapData(
            name=name,
            colors=[Color(0, 0, 0)] + colors,
            tiles=tiles,
            namespace=namespace,
            )

    export(data, template=template)


if __name__ == '__main__':
    main.run()
