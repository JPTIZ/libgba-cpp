from PyQt5.QtCore import (
        QPoint,
        )
from PyQt5.QtGui import (
        QColor,
        QImage,
        QPainter,
        )


def transparent(image, ref_color, tile_size):
    image = image.convertToFormat(QImage.Format_ARGB32)
    for x in range(image.width()):
        for y in range(image.height()):
            if image.pixelColor(x, y) == ref_color:
                image.setPixelColor(x, y, QColor(0, 0, 0, 0))
    return image


class Tileset:
    def __init__(self, filename=None, tile_size=8):
        self.filename = filename
        self.tile_size = tile_size

        self.image = None
        if filename:
            image = QImage(filename)
            self.image = transparent(image, image.pixelColor(0, 0), tile_size)


class Layer:
    def __init__(self, tileset, size=(32, 32), tile_size=8):
        self.size = size
        self.tile_size = tile_size
        self.tileset = tileset
        self.image = QImage(*self.pixel_size(), QImage.Format_ARGB32)
        self.image.fill(QColor(0, 0, 0, 0))
        self.scaling = 4

    def place(self, x, y, pattern):
        '''
        Inserts pattern on coordinates

        Args:
            x(int): x on map coordinates (not pixel's!)
            y(int): y on map coordinates (not pixel's!)
        '''
        x *= self.tile_size
        y *= self.tile_size

        painter = QPainter(self.image)
        painter.setCompositionMode(QPainter.CompositionMode_Source)
        painter.drawImage(QPoint(x, y), pattern)
        painter.end()

    def pixel_size(self):
        return (self.size[0] * self.tile_size,
                self.size[1] * self.tile_size)


class Map:
    def __init__(self, name, tileset, size=(32, 32), tile_size=8, layers=4):
        self.name = name
        self.size = size
        self.tile_size = tile_size
        self.tileset = tileset
        self.layers = [Layer(tileset) for i in range(layers)]
        for layer in self.layers:
            layer.hidden = False

    def pixel_width(self):
        return self.pixel_size()[0]

    def pixel_height(self):
        return self.pixel_size()[1]

    def pixel_size(self):
        return (self.size[0] * self.tile_size, self.size[1] * self.tile_size)


def make_image(map):
    layers = map.layers
    image = layers[0].image
    image = QImage(image.size(), image.format())
    image.fill(QColor(0, 0, 0, 0))
    painter = QPainter(image)
    for layer in layers:
        if not layer.hidden:
            painter.setOpacity(1)
        else:
            painter.setOpacity(.5)
        painter.drawImage(QPoint(0, 0), layer.image)
    painter.end()
    return image
