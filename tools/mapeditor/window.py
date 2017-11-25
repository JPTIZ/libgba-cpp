from mapeditor.editor import MapEditor

from PyQt5.QtWidgets import (
        QWidget,
        QSizePolicy,
        QHBoxLayout,
        )

class MapEditorWindow(QWidget):
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

        self.setContentsMargins(0, 0, 0, 0)


    def show(self):
        super().show()
