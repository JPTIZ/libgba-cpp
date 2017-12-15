from PyQt5.QtCore import (
        QPoint,
        )

from PyQt5.QtGui import (
        QColor,
        QImage,
        QPainter,
        )


def apply_transparency(image, tile_size):
    image = image.convertToFormat(QImage.Format_ARGB32)
    back = image.pixelColor(0, 0)
    for x in range(image.width()):
        for y in range(image.height()):
            if image.pixelColor(x, y) == back:
                image.setPixelColor(x, y, QColor(0, 0, 0, 0))
    return image


class Tileset:
    def __init__(self, filename=None, tile_size=8):
        self.filename = filename
        self.tile_size = tile_size

        self.image = None
        if filename:
            self.image = apply_transparency(QImage(filename), tile_size)


class Layer:
    def __init__(self, tileset, size=(32, 32), tile_size=8):
        self.size = size
        self.tile_size = tile_size
        self.tileset = tileset
        self.image = QImage(*self.pixel_size(), QImage.Format_ARGB32)
        self.image.fill(QColor(0, 0, 0, 0))
        self.scaling = 4

    def place_tile(self, x, y, tile_index):
        x *= self.tile_size
        y *= self.tile_size

        tileset_width = self.tileset.image.width() // 8

        sx = tile_index % tileset_width
        sy = tile_index // tileset_width

        sx *= self.tile_size
        sy *= self.tile_size

        for px in range(self.tile_size):
            for py in range(self.tile_size):
                color = self.tileset.image.pixelColor(
                        (sx + px),
                        (sy + py)
                )
                self.image.setPixelColor(px + x, py + y, color)

    def pixel_size(self):
        return (self.size[0] * self.tile_size,
                self.size[1] * self.tile_size)


class Map:
    def __init__(self, tileset, size=(32, 32), tile_size=8, layers=4):
        self.size = size
        self.tile_size = tile_size
        self.tileset = tileset
        self.layers = [Layer(tileset) for i in range(layers)]

    def pixel_width(self):
        return self.pixel_size()[0]

    def pixel_height(self):
        return self.pixel_size()[1]

    def pixel_size(self):
        return (self.size[0] * self.tile_size, self.size[1] * self.tile_size)


def make_image(map):
    layers = map.layers
    image = QImage(layers[0].image)
    painter = QPainter(image)
    for layer in layers[1:]:
        painter.drawImage(QPoint(0, 0), layer.image)
    return image
