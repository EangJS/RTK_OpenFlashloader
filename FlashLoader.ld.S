ENTRY(Init)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x8000
}

SECTIONS
{
    /* Flash os information */
    PrgCode :
    {
        . = ALIGN(4);
        KEEP(*(PrgCode PrgCode.*));
        . = ALIGN(4);
    } > RAM

    /* Text segment, stores all user code */
    .text : ALIGN(4)
    {
        /* User and library code */
        *(.text .text.*)

        KEEP(*(.init))
    } > RAM

    PrgData :
    {
        . = ALIGN(4);
        KEEP(*(PrgData PrgData.*))
        . = ALIGN(4);
    } > RAM

    /* Flash device information */
    DevDscr :
    {
        . = ALIGN(4);
        KEEP(*(DevDscr DevDscr.*));
        . = ALIGN(4);
    } > RAM

    .ARM.attributes 0 : { KEEP(*(.ARM.attributes)) }    
}


#ifdef CONFIG_AMEBADPLUS

SECTIONS
{
  PROVIDE(FLASH_Erase = 0x9fe5);
  PROVIDE(FLASH_TxData = 0x9e6d);
  PROVIDE(FLASH_Read_HandShake_Cmd = 0x96f5);
  PROVIDE(FLASH_DeepPowerDown = 0xa0c9);
  PROVIDE(WDG_Refresh = 0xd939);
  PROVIDE(_memcpy = 0x11c1d);
  PROVIDE(_memset = 0x272a9);
}

#else

SECTIONS
{
    PROVIDE(FLASH_Erase = 0x8db9);
    PROVIDE(FLASH_TxData = 0x8d31);
    PROVIDE(FLASH_Read_HandShake_Cmd = 0xe359);
    PROVIDE(FLASH_DeepPowerDown = 0x8e79);
    PROVIDE(WDG_Refresh = 0xcd29);
    PROVIDE(_memcpy = 0x7b65);
    PROVIDE(_memset = 0x7cf9);
    PROVIDE(BOOT_ROM_OSC131_Enable = 0x622b);
    PROVIDE(BOOT_ROM_SPUFlash = 0x4d45);
    PROVIDE(BOOT_ROM_InitSpic = 0x4d8f);
    PROVIDE(BOOT_ROM_ResetVsr = 0x622d);
    PROVIDE(__rom_bss_start__ = 0x20001000);
    PROVIDE(__rom_bss_end__ = 0x200014b0);
    PROVIDE(__rom_bss_start_s__ = 0x30000000);
    PROVIDE(__rom_bss_end_s__ = 0x30000500);

}

#endif
