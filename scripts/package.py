import os
import shutil
import zipfile
from pathlib import Path

target_dirs = {
    "AMEBAGREEN2": "../JLinkDevices/Realtek/AmebaGreen2",
    "AMEBADPLUS": "../JLinkDevices/Realtek/AmebaDPlus",
}

# Source directory to scan
source_dir = "../build"
jlink_devices_dir = "../JLinkDevices"
output_zip_path = "JLinkDevices.zip"

def zip_dir(source_dir, output_zip_path):
    source_dir = Path(source_dir)
    with zipfile.ZipFile(output_zip_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, dirs, files in os.walk(source_dir):
            for file in files:
                file_path = Path(root) / file
                relative_path = file_path.relative_to(source_dir.parent)
                zipf.write(file_path, relative_path)
    print(f"{source_dir} has been zipped into {output_zip_path}")

def make_package():
    for root, dirs, files in os.walk(source_dir):
        for file_name in files:
            file_path = os.path.join(root, file_name)

            if file_name.endswith(".elf"):
                target_dir = None
                for key, dir_path in target_dirs.items():
                    if key in file_name:
                        target_dir = dir_path
                        break

                if target_dir:
                    os.makedirs(target_dir, exist_ok=True)
                    shutil.copy2(file_path, target_dir)
                    print(f"Copied {file_path} to {target_dir}")
                else:
                    print(f"No target directory found for {file_name}")
    
    zip_dir(jlink_devices_dir, output_zip_path)

def main():
    make_package()

if __name__ == "__main__":
    main()
