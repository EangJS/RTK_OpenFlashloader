# Open Flashloader for Realtek Ameba MCUs

This project provides a standalone **[Open Flashloader](https://open-cmsis-pack.github.io/Open-CMSIS-Pack-Spec/main/html/flashAlgorithm.html)** implementation built using:

- **arm-none-eabi-gcc**
- **CMake**
- **Ninja**
- **Python build script**
- **CMSIS-based flash programming interface**

The output is a **`.elf`** binary compatible with SEGGER JFlash.

## Supported Ameba Boards

* AmebaDPlus  (RTL8721DXX)
* AmebaGreen2 (RTL8721F)
* AmebaSmart  (RTL8730EX)

---

## ✅ Requirements

| Dependency | Purpose |
|-----------|---------|
| arm-none-eabi-gcc | Cross compiler
| CMake ≥ 3.20 | Build generator |
| Ninja | Fast build tool |
| Python 3 | Build automation |

---

## 🚀 Build Instructions

From the project root:

```sh
./build.py
```

to perform build on all supported chips.

To perform a clean build
```
rm -rf build/
```
Then run `build.py`

## Output Files
After a successful build, you will find:

```
output/
└── CHIPNAME_FLASHSIZE.elf
```

## Usage
> SEGGER JFLASH

#### Requirements
* SEGGER JLINK PLUS or higher

#### Installation

### Automated Installation

1. `cd` into the `scripts` directory.

2. Build the installer by first executing `package.py` and then `CI.py`

3. Execute the `RTKJLinkDevicesInstaller` executable.

---

### Manual Installation

> [!NOTE]
> AmebaDPlus is used as the example

Copy the respective device `.xml` located in `devices/` to the following directory: 

Windows
`C:\Users\user\AppData\Roaming\SEGGER\JLinkDevices\Realtek\AmebaDPlus\RTL8721DXX.xml`

or

Linux `/home/user/.SEGGER/JLinkDevices\Realtek\AmebaDPlus\RTL8721DXX.xml`


Place the `FlashLoader.elf` in the same level directory as the `RTL8721DXX.xml`

> [!NOTE] 
> You should have already added the jlink_scripts into a folder called `JLinkDevices\Realtek\AmebaDPlus\jlink_script`


Reference: [J-Link Device Support Kit](https://kb.segger.com/J-Link_Device_Support_Kit)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
