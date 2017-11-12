from os.path import abspath
from typing import NamedTuple, List

from carl import command
from jinja2 import Environment, FileSystemLoader
from PIL import Image


def lookahead(iterable):
    it = iter(iterable)
    prev = next(it)
    for val in it:
        yield prev, True
        prev = val
    yield prev, False


class Color(NamedTuple):
    r: int
    g: int
    b: int


class MapData(NamedTuple):
    name: str
    colors: List[Color]
    tiles: List[List[List[int]]]


def export(data, output='output.h'):
    latex_env = Environment(
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
    latex_env.filters['lookahead'] = lookahead
    tiles = [
        [sum(v << (i * 8) for i, v in enumerate(row))
            for row in tile] for tile in data.tiles]
    with open(output, 'w') as f:
        template = latex_env.get_template('template.h')
        f.write(template.render(
            namespace='resources',
            name=data.name,
            n_colors=len(data.colors),
            n_tiles=len(tiles),
            colors=data.colors,
            tiles=tiles))


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
    return tiles


@command
def main(bitmap: 'Bitmap file to be read.',
         template: 'Template header file.' = 'template.h'):
    image = Image.open(bitmap).convert(
                mode='P',
                palette=Image.ADAPTIVE,
                colors=255)

    palette = image.palette.palette
    colors = [Color(0, 0, 0)] + [
                Color(palette[i + 0] // 8,
                      palette[i + 1] // 8,
                      palette[i + 2] // 8)
                for i in range(0, len(palette), 3)]

    pixels = image.load()
    tiles = extract_tiles(image, pixels)
    data = MapData(
            name='sample',
            colors=colors,
            tiles=tiles,
            )

    export(data)


if __name__ == '__main__':
    main.run()
