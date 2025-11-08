# Open Flashloader for Realtek Ameba MCUs

This project provides a standalone **[Open Flashloader](https://open-cmsis-pack.github.io/Open-CMSIS-Pack-Spec/main/html/flashAlgorithm.html)** implementation built using:

- **arm-none-eabi-gcc**
- **CMake**
- **Ninja**
- **Python build script**
- **CMSIS-based flash programming interface**

The output is a **`.elf`** binary compatible with SEGGER JFlash.

## Supported Ameba Boards

* AmebaDPlus (RTL8721DXX)
* More to come...

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

Add the flashloader into the `.xml` of the device profile to use in 

Windows
`C:\Users\user\AppData\Roaming\SEGGER\JLinkDevices\Realtek\AmebaDPlus\RTL8721DXX.xml`

or

Linux `/home/user/.SEGGER/JLinkDevices\Realtek\AmebaDPlus\RTL8721DXX.xml`

```xml
<Database>
  <Device>
    <ChipInfo Vendor="Realtek" Name="RTL8721DX_KM4" Core="JLINK_CORE_CORTEX_M55" WorkRAMAddr="0x3000A020" WorkRAMSize="0x8000" JLinkScriptFile="jlink_script/AP2_KM4.JLinkScript" />
    <FlashBankInfo Name="NOR Flash" BaseAddr="0x08000000">
      <LoaderInfo Name="Default" MaxSize="0x01000000" Loader="FlashLoader.elf" LoaderType="FLASH_ALGO_TYPE_OPEN" />
    </FlashBankInfo>
  </Device>
  <Device>
    <ChipInfo Vendor="Realtek" Name="RTL8721DX_KM0" Core="JLINK_CORE_CORTEX_M23" JLinkScriptFile="jlink_script/AP1_KM0.JLinkScript" />
  </Device>
</Database>
```

Place the FlashLoader.elf in the same level directory as the `RTL8721DXX.xml`

> [!NOTE] 
> You should have already added the jlink_scripts into a folder called `JLinkDevices\Realtek\AmebaDPlus\jlink_script`


Reference: [J-Link Device Support Kit](https://kb.segger.com/J-Link_Device_Support_Kit)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
