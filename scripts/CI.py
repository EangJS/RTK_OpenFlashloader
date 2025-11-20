import os
import sys
import subprocess
from pathlib import Path
import shutil

# -------------------------
# CONFIGURATION
# -------------------------
PROJECT_DIR = Path(__file__).parent.resolve()
SCRIPT_NAME = "installer.py"       # Your installer script
PAYLOAD_ZIP = "JLinkDevices.zip"        # ZIP file to embed
DIST_DIR = PROJECT_DIR / "dist"    # Output directory
BUILD_DIR = PROJECT_DIR / "build"  # PyInstaller build directory
EXE_NAME = "SEGGERInstaller"   # Final EXE name

# -------------------------
# UTILITY FUNCTIONS
# -------------------------
def check_file_exists(path):
    if not path.exists():
        print(f"Error: {path} not found.")
        sys.exit(1)

def run_command(cmd):
    print(f"Running: {' '.join(cmd)}")
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print("Error:")
        print(result.stdout)
        print(result.stderr)
        sys.exit(result.returncode)
    else:
        print(result.stdout)

# -------------------------
# MAIN BUILD SCRIPT
# -------------------------
def main():
    # Check files
    script_path = PROJECT_DIR / SCRIPT_NAME
    zip_path = PROJECT_DIR / PAYLOAD_ZIP
    check_file_exists(script_path)
    check_file_exists(zip_path)

    # Clean old build/dist folders
    if BUILD_DIR.exists():
        shutil.rmtree(BUILD_DIR)
    if DIST_DIR.exists():
        shutil.rmtree(DIST_DIR)

    # Build PyInstaller command
    # Windows format for --add-data: "source;dest"
    if sys.platform == "win32":
        add_data_option = f"{PAYLOAD_ZIP}:."
    else:
        add_data_option = f"{PAYLOAD_ZIP}:."
    cmd = [
        "pyinstaller",
        "--onefile",
        "--noconsole",   # Remove console window
        f"--name={EXE_NAME.replace('.exe','')}",
        f"--add-data={add_data_option}",
        SCRIPT_NAME
    ]

    run_command(cmd)

    # Move the final EXE to dist/EXE_NAME
    if sys.platform == "win32":
        built_exe = DIST_DIR / f"{EXE_NAME}.exe"
    else:
        built_exe = DIST_DIR / EXE_NAME
    if built_exe.exists():
        print(f"Build complete: {built_exe}")

if __name__ == "__main__":
    main()
