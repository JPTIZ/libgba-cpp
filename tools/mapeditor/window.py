from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (
        QAction,
        QActionGroup,
        QHBoxLayout,
        QSizePolicy,
        QMainWindow,
        QWidget,
        )
from PyQt5.QtGui import (
        QIcon,
        )

from mapeditor.editor import MapEditor
from mapeditor.gen import export


class MapEditorWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.build_menubar()
        self.build_toolbar()

        self.editor = MapEditorWindowContents(self)
        self.setCentralWidget(self.editor)

        self.select_layer(0)

    def build_menubar(self):
        bar = self.menuBar()
        bar.setNativeMenuBar(True)
        file_menu = bar.addMenu('&File')
        file_menu.addAction(QAction('&New', self))

        export_menu = file_menu.addMenu('E&xport')

        export_all = QAction('&All', self)
        export_all.triggered.connect(self.export_all)

        export_cpp = QAction('.&cpp', self)
        export_cpp.triggered.connect(self.export_cpp)

        export_header = QAction('.&h', self)
        export_header.triggered.connect(self.export_header)

        export_menu.addAction(export_all)
        export_menu.addAction(export_cpp)
        export_menu.addAction(export_header)

    def build_toolbar(self):
        self.toolbar = self.addToolBar('Layers')

        self.build_layer_actions()

        self.toolbar.addActions(self.layers_group.actions())

    def build_layer_actions(self):
        self.layers_group = QActionGroup(self)
        self.layer_actions = [QAction(
                                QIcon(f'mapeditor/layer{i}_icon.png'),
                                f'Layer {i}',
                                self) for i in range(4)]

        shortcuts = [Qt.Key_F5,
                     Qt.Key_F6,
                     Qt.Key_F7,
                     Qt.Key_F8, ]

        for i, action in enumerate(self.layer_actions):
            action.layer_index = i
            action.setCheckable(True)
            action.triggered.connect(self.on_select_layer)
            action.setShortcut(shortcuts[i])
            self.layers_group.addAction(action)

    def on_select_layer(self, b):
        self.select_layer(self.sender().layer_index)

    def select_layer(self, index):
        self.layer_actions[index].setChecked(True)
        self.editor.select_layer(index)

    def export_all(self, *args):
        print('exporting all')
        export(self.editor.editor.map,
               namespace='test',
               output='test')

    def export_cpp(self, *args):
        print('exporting cpp')
        export(self.editor.editor.map,
               namespace='test',
               output='test',
               exts=('cpp',))

    def export_header(self, *args):
        print('exporting header')
        export(self.editor.editor.map,
               namespace='test',
               output='test',
               exts=('h',))


class MapEditorWindowContents(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.setWindowTitle('Map editor')
        self.maximized = True
        self._width, self._height = 800, 600
        self.setMinimumSize(self._width, self._height)

        self.editor = MapEditor(self, tileset='forest-tileset.bmp')
        self.editor.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        layout = QHBoxLayout(self)
        layout.addWidget(self.editor)

        self.setContentsMargins(-6, -6, -6, -6)

    def select_layer(self, index):
        self.editor.select_layer(index)

    def show(self):
        super().show()
