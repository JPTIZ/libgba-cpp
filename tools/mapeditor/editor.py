from PyQt5.QtCore import (
        pyqtSignal,
        QEvent,
        QPoint,
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
        QPixmap,
        )


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

        self.tilemap = TilemapEditor(self.tileset)
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

        self.tileset = tileset
        self.width = self.tile_size*8

        self.tile_index = 0

        if tileset:
            self.image = QImage(self.tileset)
            self.setPixmap(
                    QPixmap(tileset).scaledToWidth(self.width))

        self.mousePressEvent = self.onclick


    def onclick(self, event):
        pos = event.pos()
        x, y = pos.x() // self.tile_size, pos.y() // self.tile_size
        self.tile_index = x + y * 8
        self.repaint()


    def paintEvent(self, e):
        super().paintEvent(e)

        if self.tile_index < 0:
            return

        painter = QPainter(self)
        painter.setPen(QColor(255, 255, 255))

        x, y = self.tile_index % 8, self.tile_index // 8

        painter.drawRect(QRect(x * self.tile_size, y * self.tile_size, self.tile_size - 1, self.tile_size - 1))
        painter.end()


class TilemapEditor(QLabel):
    def __init__(self, tileset, *args, map_size=(32,32), **kwargs):
        super().__init__(*args, **kwargs)
        print('yay')

        self.scaling = 4
        self.tile_size = self.scaling * 8
        self.map_size = (map_size[0] * self.tile_size, map_size[1] * self.tile_size)

        self.tileset = tileset

        self.image = QImage(*self.map_size, QImage.Format_ARGB32)

        self.setPixmap(QPixmap.fromImage(self.image))
        self.mousePressEvent = self.onclick
        self.mouseMoveEvent = self.onclick


    def onclick(self, e):
        pos = e.pos()
        x, y = pos.x() // self.tile_size, pos.y() // self.tile_size
        print((x, y))

        #bits = self.image.bits()

        #bits[x + self.map_size[0] * y] = 255

        tile_index = self.tileset.tile_index

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
                        (sx + px) // self.scaling,
                        (sy + py) // self.scaling
                )
                self.image.setPixelColor(QPoint(px + x, py + y), color)

        self.setPixmap(QPixmap.fromImage(self.image))
