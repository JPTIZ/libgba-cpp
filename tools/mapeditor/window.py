from PyQt5.QtCore import Qt

from PyQt5.QtWidgets import (
        QAction,
        QHBoxLayout,
        QSizePolicy,
        QMainWindow,
        QWidget,
        )

from PyQt5.QtGui import (
        QIcon,
        )

from mapeditor.editor import MapEditor


class MapEditorWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.editor = MapEditorWindowContents(self)
        self.setCentralWidget(self.editor)

        self.toolbar = self.addToolBar('Layers')
        self.layer_actions = [QAction(
                                QIcon(f'layer{i}_icon.png'),
                                f'Layer {i}',
                                self) for i in range(4)]
        for i, action in enumerate(self.layer_actions):
            action.layer_index = i
            action.setCheckable(True)
            action.triggered.connect(self.select_index)
            self.toolbar.addAction(action)
        self.select_layer(0)

    def select_index(self, b):
        action = self.sender()
        action.setChecked(b)
        self.select_layer(action.layer_index)

    def select_layer(self, index):
        for i, action in enumerate(self.layer_actions):
            action.setChecked(i == index)
        self.editor.select_layer(index)

    def keyPressEvent(self, e):
        if e.key() == Qt.Key_F5:
            self.select_layer(0)
        elif e.key() == Qt.Key_F6:
            self.select_layer(1)
        elif e.key() == Qt.Key_F7:
            self.select_layer(2)
        elif e.key() == Qt.Key_F8:
            self.select_layer(3)


class MapEditorWindowContents(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.setWindowTitle('Map editor')
        self.maximized = True
        self.width, self.height = 800, 600
        self.setMinimumSize(self.width, self.height)

        self.editor = MapEditor(self, tileset='forest-tileset.bmp')
        self.editor.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        layout = QHBoxLayout(self)
        layout.addWidget(self.editor)

        self.setContentsMargins(-6, -6, -6, -6)

    def select_layer(self, index):
        self.editor.select_layer(index)

    def show(self):
        super().show()
