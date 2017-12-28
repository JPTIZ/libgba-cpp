from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (
        QAction,
        QActionGroup,
        QFileDialog,
        QHBoxLayout,
        QSizePolicy,
        QMainWindow,
        QWidget,
        )
from PyQt5.QtGui import (
        QIcon,
        )

from mapeditor.editor import MapEditor
from mapeditor.gen import export, save, load


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

        menus = {
                    '&File': {
                        '&New': (self.new, 'Ctrl+N'),
                        '&Open': (self.open, 'Ctrl+O'),
                        '&Save': (self.save, 'Ctrl+S'),
                        'E&xport': [
                            ('&All', self.export_all),
                            ('.&cpp', self.export_cpp),
                            ('.&h', self.export_header),
                        ],
                    },
                }

        for name, items in menus.items():
            menu = bar.addMenu(name)
            for item, value in items.items():
                if isinstance(value, list):
                    submenu = menu.addMenu(item)
                    for name, function in value:
                        action = QAction(name, self)
                        action.triggered.connect(function)
                        submenu.addAction(action)
                elif isinstance(value, tuple):
                    function, shortcut = value
                    action = QAction(item, self)
                    action.setShortcut(shortcut)
                    action.triggered.connect(function)
                    menu.addAction(action)
                else:
                    action = QAction(item, self)
                    action.triggered.connect(value)
                    menu.addAction(action)

    def new(self):
        print('new (not implemented)')

    def open(self):
        dialog = QFileDialog(self, 'Open map')
        dialog.setFileMode(QFileDialog.ExistingFile)
        if dialog.exec():
            filename, = dialog.selectedFiles()
            self.editor.load(load(filename))

    def save(self):
        dialog = QFileDialog(self, 'Open map')
        dialog.setAcceptMode(QFileDialog.AcceptSave)
        if dialog.exec():
            filename, = dialog.selectedFiles()
            save(self.editor.editor.map, filename)

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
        export(self.editor.editor.map,
               namespace='test',
               output='test')

    def export_cpp(self, *args):
        export(self.editor.editor.map,
               namespace='test',
               output='test',
               exts=('cpp',))

    def export_header(self, *args):
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

    def load(self, data):
        self.editor.load(data)

    def select_layer(self, index):
        self.editor.select_layer(index)

    def show(self):
        super().show()
