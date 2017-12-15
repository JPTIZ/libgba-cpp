from PyQt5.QtCore import (
        QRect,
        Qt,
        )

from PyQt5.QtWidgets import (
        QHBoxLayout,
        QLabel,
        QScrollArea,
        QSizePolicy,
        QWidget,
        )

from PyQt5.QtGui import (
        QColor,
        QPainter,
        QPen,
        QPixmap,
        )

from mapeditor.map import Tileset, Map, make_image


class MapEditor(QWidget):
    def __init__(self, *args, tileset=None, **kwargs):
        super().__init__(*args, **kwargs)

        self.map = Map(
                tileset=Tileset(filename=tileset),
                size=(32, 32),
                tile_size=8,
                layers=4
                )

        contents = QHBoxLayout(self)

        self.tileset_selector = TilesetSelector(self, tileset=self.map.tileset)
        left = QScrollArea()
        left.setWidget(self.tileset_selector)
        left.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        left.setStyleSheet('background: url(\'square.png\') repeat;')

        self.tilemap = TilemapEditor(
                self.map,
                tileset_selector=self.tileset_selector
                )
        self.tilemap.setStyleSheet('background: url(\'square.png\') repeat;')
        right = QScrollArea()
        right.setWidget(self.tilemap)

        contents.addWidget(left)
        contents.addWidget(right)

        left.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Expanding)
        right.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        contents.setContentsMargins(0, 0, 0, 0)


class TilesetSelector(QLabel):
    '''
    Widget for selecting tiles used to fill map.
    '''
    def __init__(self, *args, tileset=None, tile_size=32, **kwargs):
        super().__init__(*args, **kwargs)

        self.index = -1
        self.tileset = tileset
        self.tile_size = 32
        self.width = 256

        if self.tileset.image:
            self.setPixmap(QPixmap.fromImage(self.tileset.image)
                                  .scaledToWidth(self.width))

        self.mousePressEvent = self.onclick

    def onclick(self, event):
        pos = event.pos()
        x, y = pos.x() // self.tile_size, pos.y() // self.tile_size
        self.index = x + y * self.tileset.tile_size
        self.repaint()

    def paintEvent(self, e):
        super().paintEvent(e)

        index = self.index

        if index < 0:
            return

        painter = QPainter(self)
        painter.setPen(QPen(QColor(0, 0, 0), 3))

        x, y = index % 8, index // 8
        rect = QRect(x * self.tile_size,
                     y * self.tile_size,
                     self.tile_size - 1,
                     self.tile_size - 1)

        painter.drawRect(rect)
        painter.setPen(QPen(QColor(255, 255, 255), 1))
        painter.drawRect(rect)
        painter.end()


class TilemapEditor(QLabel):
    '''
    Widget to show and edit the map itself.
    '''
    def __init__(self,
                 map,
                 *args,
                 tileset_selector=None,
                 **kwargs):
        super().__init__(*args, **kwargs)

        self.map = map
        self._current_layer = 0
        self.tileset_selector = tileset_selector
        self.scaling = 4

        self.remake_image()

        self.mousePressEvent = self.onclick
        self.mouseMoveEvent = self.onclick

    def current_layer(self):
        return self.map.layers[self._current_layer]

    def remake_image(self):
        self.setPixmap(QPixmap.fromImage(make_image(self.map))
                              .scaledToWidth(
                                  self.map.pixel_width() * self.scaling))

    def onclick(self, e):
        tileset = self.tileset_selector
        if tileset.index < 0:
            return
        pos = e.pos()
        scale = self.map.tile_size * self.scaling
        x, y = pos.x() // scale, pos.y() // scale

        self.current_layer().place_tile(x, y, tileset.index)
        self.remake_image()
