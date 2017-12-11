from PyQt5.QtCore import (
        pyqtSignal,
        QEvent,
        QRect,
        QObject,
        Qt,
        )

from PyQt5.QtWidgets import (
        QFrame,
        QHBoxLayout,
        QLabel,
        QScrollArea,
        QSizePolicy,
        QWidget,
        )

from PyQt5.QtGui import (
        QColor,
        QImage,
        QPainter,
        QPen,
        QPixmap,
        )

from mapeditor.map import Tileset, Map


def clickable(widget):
    class Filter(QObject):
        clicked = pyqtSignal()

        def eventFilter(self, obj, event):
            if (obj == widget and event.type() == QEvent.MouseButtonRelease and
                obj.rect().contains(event.pos())):
                    self.clicked.emit()
                    return True
            return False

    filtered = Filter(widget)
    widget.installEventFilter(filtered)
    return filtered.clicked


class MapEditor(QWidget):
    def __init__(self, *args, tileset=None, **kwargs):
        super().__init__(*args, **kwargs)

        self.tileset = TilesetSelector(self, tileset=tileset)

        self.tilemap = TilemapEditor(self.tileset.tileset)
        self.tilemap.setStyleSheet('background: url(\'square.png\') repeat;')

        contents = QHBoxLayout(self)

        left = QScrollArea()
        left.setWidget(self.tileset)
        left.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        left.setStyleSheet('background: url(\'square.png\') repeat;')

        right = QScrollArea()
        right.setWidget(self.tilemap)

        contents.addWidget(left)
        contents.addWidget(right)

        left.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Expanding)
        right.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        contents.setContentsMargins(0, 0, 0, 0)


class TilesetSelector(QLabel):
    def __init__(self, *args, tileset=None, **kwargs):
        super().__init__(*args, **kwargs)

        self.scaling = 4
        self.tile_size = self.scaling * 8

        self.tileset = Tileset(filename=tileset)
        self.width = self.tile_size * 8

        if self.tileset.image:
            self.setPixmap(QPixmap.fromImage(self.tileset.image)
                                  .scaledToWidth(self.width))

        self.mousePressEvent = self.onclick


    def onclick(self, event):
        pos = event.pos()
        x, y = pos.x() // self.tile_size, pos.y() // self.tile_size
        self.tileset.index = x + y * self.tileset.tile_size
        self.repaint()


    def paintEvent(self, e):
        super().paintEvent(e)

        index = self.tileset.index

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
    def __init__(self, tileset, *args, map_size=(32,32), **kwargs):
        super().__init__(*args, **kwargs)

        self.tileset = tileset

        self.scaling = 4
        self.tile_size = self.tileset.tile_size

        self.map = Map(
                tileset=tileset,
                size=(map_size[0] * self.tile_size,
                      map_size[1] * self.tile_size),
                tile_size=8
                )

        self.remake_image()

        self.mousePressEvent = self.onclick
        self.mouseMoveEvent = self.onclick


    def remake_image(self):
        self.setPixmap(QPixmap.fromImage(self.map.image)
                              .scaledToWidth(
                                  self.map.image.width() * self.scaling))


    def onclick(self, e):
        if self.tileset.index < 0:
            return
        pos = e.pos()
        scale = self.tile_size * self.scaling
        x, y = pos.x() // scale, pos.y() // scale

        self.map.place_tile(x, y, self.tileset.index)
        self.remake_image()
