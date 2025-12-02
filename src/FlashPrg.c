/**************************************************************************//**
 * @file     FlashPrg.c
 * @brief    Flash Programming Functions adapted for RTL87XX Devices
 * @version  V1.0.0
 * @date     11. November 2025
 ******************************************************************************/
/*
 * Copyright (c) 2010-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "FlashOS.h"
#include <stdint.h>
#include "ameba.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define PRG_CODE_SECTION __attribute__((section(".PrgCode")))

/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
PRG_CODE_SECTION int Init( uint32_t adr, uint32_t clk, uint32_t fnc )
{
    
#ifdef AMEBAGREEN2
    _memset((void *) __rom_bss_start__, 0, (__rom_bss_end__ - __rom_bss_start__));
    _memset((void *) __rom_bss_start_s__, 0, (__rom_bss_end_s__ - __rom_bss_start_s__));
    BOOT_ROM_OSC131_Enable();
    BOOT_ROM_SPUFlash();
    BOOT_ROM_InitSpic();
#endif /* AMEBAGREEN2 */

    SCB_DisableDCache();
    WDG_Refresh( IWDG_DEV );
#ifndef AMEBASMART
    FLASH_Read_HandShake_Cmd( 0, 0 );
    FLASH_DeepPowerDown( 0 );
#else
    uint32_t boot_from_nor = SYSCFG_BootFromNor();
    if (boot_from_nor) {
        /* Nor Flash, already initialized when boot */
    } else {
        while(1); // Not support to program when boot from SPI NAND
    }
#endif /* AMEBASMART */


    return 0;
}

/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
PRG_CODE_SECTION int UnInit( uint32_t fnc )
{
    return 0;
}

/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */
PRG_CODE_SECTION int EraseChip( void )
{
    FLASH_Erase( ERASE_CHIP, 0U );
    
    return 0;
}

/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */
PRG_CODE_SECTION int EraseSector( uint32_t adr )
{
    WDG_Refresh( IWDG_DEV );
    FLASH_Erase( ERASE_SECTOR, adr );
    return 0;
}

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */
PRG_CODE_SECTION int ProgramPage(uint32_t adr, uint32_t sz, unsigned char *buf)
{
    WDG_Refresh(IWDG_DEV);

    const uint32_t phys_page = 0x100;
    uint32_t offset = 0;

    while (offset < sz)
    {
        uint32_t tx_len = MIN(phys_page, sz - offset);

        if ((adr + offset) % phys_page != 0) {
            return -1;
        }

        FLASH_TxData(adr + offset, tx_len, buf + offset);
        WDG_Refresh(IWDG_DEV);

        offset += tx_len;
    }

    return 0;
}
