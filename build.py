#!/usr/bin/env python3
import os
import subprocess
import sys

PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))
BUILD_DIR = os.path.join(PROJECT_ROOT, "build")

CMAKE_GENERATOR = "Ninja"

devices = ["AMEBAGREEN2", "AMEBADPLUS"]

def run_cmd(cmd, cwd=None):
    print(f"\n>>> {' '.join(cmd)}")
    result = subprocess.run(cmd, cwd=cwd)
    if result.returncode != 0:
        print(f"❌ Command failed: {' '.join(cmd)}")
        sys.exit(result.returncode)

def build_device(device):
    with open("project.config", "w") as f:
        f.write(f"CONFIG_{device}=y\n")
    print(f"Building for device: {device}")
    run_cmd([
        "cmake",
        "-G", CMAKE_GENERATOR,
        PROJECT_ROOT
    ], cwd=BUILD_DIR)
    run_cmd(["ninja"], cwd=BUILD_DIR)

def main():
    print("=== Open Flashloader Build ===")

    os.makedirs(BUILD_DIR, exist_ok=True)

    for device in devices:
        build_device(device)
        target_name = f"{device}.elf"
        elf_src = os.path.join(BUILD_DIR, target_name)
        if os.path.isfile(elf_src):
            print(f"✅ Built: {elf_src}")

    print("\n✅ Build completed successfully!")

if __name__ == "__main__":
    main()
