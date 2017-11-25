import sys

from PyQt5.QtWidgets import QApplication

from mapeditor.window import MapEditorWindow

app = QApplication(sys.argv)
editor = MapEditorWindow()
editor.show()
sys.exit(app.exec_())
