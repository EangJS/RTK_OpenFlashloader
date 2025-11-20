import sys
import os
from pathlib import Path
import zipfile

from PyQt6.QtWidgets import QApplication, QWidget, QFileDialog, QPushButton, QLabel, QVBoxLayout
from PyQt6.QtGui import QPixmap

def resource_path(relative_path):
    """Return absolute path to resource in development or PyInstaller bundle."""
    if hasattr(sys, "_MEIPASS"):
        return Path(sys._MEIPASS) / relative_path
    return Path(__file__).parent / relative_path

def get_default_target_dir():
    """Target AppData folder for the device."""
    if sys.platform == "win32":
        return Path(os.getenv("APPDATA")) / "SEGGER"
    elif sys.platform == "darwin":
        return Path.home() / "Library" / "Application Support" / "SEGGER"
    else:
        return Path.home() / ".config" / "SEGGER"

def extract_zip(zip_path, dest_dir):
    dest_dir.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(zip_path, 'r') as z:
        z.extractall(dest_dir)

class InstallerWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("SEGGER Installer")

        self.default_dest = get_default_target_dir()
        self.selected_dest = self.default_dest

        # Widgets
        self.label = QLabel(f"Install to: {self.selected_dest}")
        self.select_button = QPushButton("Choose Install Directory")
        self.install_button = QPushButton("Install")
        self.ok_button = QPushButton("OK")
        self.ok_button.hide()  # hide initially

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.select_button)
        layout.addWidget(self.install_button)
        layout.addWidget(self.ok_button)
        self.setLayout(layout)

        # Connections
        self.select_button.clicked.connect(self.select_directory)
        self.install_button.clicked.connect(self.install)
        self.ok_button.clicked.connect(self.close)  # closes the window

    def select_directory(self):
        folder = QFileDialog.getExistingDirectory(self, "Select Install Directory", str(self.default_dest))
        if folder:
            self.selected_dest = Path(folder)
            self.label.setText(f"Install to: {self.selected_dest}")

    def install(self):
        zip_path = resource_path("JLinkDevices.zip")
        extract_zip(zip_path, self.selected_dest)
        
        # Update UI after install
        self.select_button.hide()
        self.install_button.hide()
        self.label.setText(f"Installation complete at {self.selected_dest}")

        # Show OK button to close
        self.ok_button.show()

def main():
    app = QApplication(sys.argv)
    window = InstallerWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
