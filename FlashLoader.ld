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

SECTIONS
{
  PROVIDE(FLASH_Erase = 0x9fe5);
  PROVIDE(FLASH_TxData = 0x9e6d);
  PROVIDE(RCC_PeriphClockSource_SPIC = 0xbfe5);
  PROVIDE(FLASH_Read_HandShake_Cmd = 0x96f5);
  PROVIDE(FLASH_DeepPowerDown = 0xa0c9);
  PROVIDE(WDG_Refresh = 0xd939);
  PROVIDE(_memcpy = 0x11c1d);
}
