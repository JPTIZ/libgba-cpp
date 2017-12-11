from typing import Tuple, NamedTuple

from PyQt5.QtCore import (
        QPoint,
        )

from PyQt5.QtGui import (
        QImage,
        )


class Tileset:
    def __init__(self, filename=None, tile_size=8):
        self.filename = filename
        self.index = -1
        self.tile_size = tile_size

        self.image = None
        if filename:
            self.image = QImage(filename)


class Map():
    def __init__(self, tileset, size=(32, 32), tile_size=8):
        self.size = size
        self.tile_size = tile_size
        self.tileset = tileset
        self.image = QImage(*self.size, QImage.Format_ARGB32)
        self.scaling = 4

    def place_tile(self, x, y, tile_index):
        x *= self.tile_size
        y *= self.tile_size

        tileset_width = self.tileset.image.width() // 8

        print(f'tiles in row: {tileset_width}')

        sx = tile_index % tileset_width
        sy = tile_index // tileset_width

        print(f'src: ({sx, sy})')

        sx *= self.tile_size
        sy *= self.tile_size

        for px in range(self.tile_size):
            for py in range(self.tile_size):
                color = self.tileset.image.pixelColor(
                        (sx + px),
                        (sy + py)
                )
                self.image.setPixelColor(QPoint(px + x, py + y), color)
