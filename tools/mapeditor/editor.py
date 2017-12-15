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


def scaled(rect, scale):
    rect = QRect(
            rect.x() * scale,
            rect.y() * scale,
            rect.width() * scale,
            rect.height() * scale)
    return rect


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

    def select_layer(self, index):
        self.tilemap._current_layer = index

    def keyPressEvent(self, e):
        old_layer = self.tilemap._current_layer

        if e.key() == Qt.Key_F5:
            self.select_layer(0)
        elif e.key() == Qt.Key_F6:
            self.select_layer(1)
        elif e.key() == Qt.Key_F7:
            self.select_layer(2)

        curr_layer = self.tilemap._current_layer
        if old_layer != curr_layer:
            print(f'switched to layer {curr_layer}')


class TilesetSelector(QLabel):
    '''
    Widget for selecting tiles used to fill map.
    '''
    def __init__(self, *args, tileset=None, tile_size=32, **kwargs):
        super().__init__(*args, **kwargs)

        self.tileset = tileset
        self.tile_size = self.tileset.tile_size
        self.width = 256
        self.sel_rect = None

        self.scaling = 4
        self.tiles_per_row = self.width // (self.tile_size * self.scaling)

        if self.tileset.image:
            self.setPixmap(QPixmap.fromImage(self.tileset.image)
                                  .scaledToWidth(self.width))

        self.mousePressEvent = self.onclick
        self.mouseMoveEvent = self.ondrag

    def scale(self):
        return self.tile_size * self.scaling

    def scaled(self, x, y):
        scale = self.scale()
        return self.scale() * (x // scale), self.scale() * (y // scale)

    def ondrag(self, event):
        scale = self.scale()

        x, y = self.origin

        pos = event.pos()
        ex, ey = pos.x() // scale, pos.y() // scale
        ox, oy = self.origin

        r1 = QRect(ox, oy, 1, 1)
        r2 = QRect(ex, ey, 1, 1)
        self.sel_rect = r1 | r2

        self.repaint()

    def onclick(self, event):
        scale = self.scale()

        pos = event.pos()
        x, y = self.scaled(pos.x(), pos.y())
        self.origin = x // scale, y // scale
        self.sel_rect = QRect(x, y, scale, scale)
        self.repaint()

    def paintEvent(self, e):
        super().paintEvent(e)

        if not self.sel_rect:
            return

        painter = QPainter(self)
        painter.setPen(QPen(QColor(0, 0, 0), 3))

        rect = scaled(self.sel_rect, self.scale())
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
        scale = self.map.tile_size * self.scaling

        pos = e.pos()
        x, y = pos.x() // scale, pos.y() // scale

        if not self.contentsRect().contains(pos.x(), pos.y()):
            return

        tileset = self.map.tileset
        rect = scaled(self.tileset_selector.sel_rect, self.map.tile_size)
        pattern = tileset.image.copy(rect)
        self.current_layer().place(x, y, pattern)
        self.remake_image()
