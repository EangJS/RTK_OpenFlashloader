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

Configure the chipset to build by setting defines in `project.config`

> Only 1 chipset can be used at a time.

#### Options
* CONFIG_AMEBAGREEN2=y
* CONFIG_AMEBADPLUS=y

From the project root:

```sh
./build.py
```

To perform a clean build
```
rm -rf build/
```
Then run `build.py`

## Output Files
After a successful build, you will find:

```
output/
└── FlashLoader.elf
```

## Usage
> SEGGER JFLASH

#### Requirements
* SEGGER JLINK PLUS or higher

#### Installation
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
