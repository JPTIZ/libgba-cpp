from PyQt5.QtCore import (
        pyqtSignal,
        QEvent,
        QObject,
        )

from PyQt5.QtWidgets import (
        QFrame,
        QHBoxLayout,
        QLabel,
        QScrollArea,
        QSizePolicy,
        QWidget,
        )

from PyQt5.QtCore import Qt

from PyQt5.QtGui import QImage, QPixmap

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

        you = QLabel()
        you.setText('')

        contents = QHBoxLayout(self)

        left = QScrollArea()
        left.setWidget(self.tileset)
        left.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        left.setStyleSheet('background: url(\'square.png\') repeat;')

        right = QScrollArea()
        right.setWidget(you)

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

        if tileset:
            self.setPixmap(
                    QPixmap(tileset).scaledToWidth(self.width))

        self.mousePressEvent = self.onclick


    def onclick(self, event):
        pos = event.pos()
        x, y = pos.x() // self.tile_size, pos.y() // self.tile_size
        print(f'clicked in ({x}, {y})')
