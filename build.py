#!/usr/bin/env python3
import os
import subprocess
import sys
import shutil

PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))
BUILD_DIR = os.path.join(PROJECT_ROOT, "build")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "output")

CMAKE_GENERATOR = "Ninja"

TARGET = "FlashLoader.elf"

def run_cmd(cmd, cwd=None):
    print(f"\n>>> {' '.join(cmd)}")
    result = subprocess.run(cmd, cwd=cwd)
    if result.returncode != 0:
        print(f"❌ Command failed: {' '.join(cmd)}")
        sys.exit(result.returncode)

def main():
    print("=== Open Flashloader Build ===")

    os.makedirs(BUILD_DIR, exist_ok=True)
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    run_cmd([
        "cmake",
        "-G", CMAKE_GENERATOR,
        PROJECT_ROOT
    ], cwd=BUILD_DIR)

    run_cmd(["ninja"], cwd=BUILD_DIR)

    elf_src = os.path.join(BUILD_DIR, TARGET)
    elf_dst = os.path.join(OUTPUT_DIR, TARGET)

    if os.path.exists(elf_src):
        shutil.copy(elf_src, elf_dst)
        print(f"✅ Output: {elf_dst}")
    else:
        print("⚠ ELF not found! Check build logs.")
        sys.exit(1)

    print("\n✅ Build completed successfully!")

if __name__ == "__main__":
    main()
