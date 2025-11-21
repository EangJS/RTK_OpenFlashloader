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
 
#include "FlashOS.h"        // FlashOS Structures
#include "config.h"

#ifdef AMEBAGREEN2

__attribute__((section("DevDscr"))) 
#if defined(CONFIG_FLASH_SIZE_16MB)

struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,                      // Driver Version
    "GD25Q32 16MB External QSPI Flash",   // Device Name
    EXTSPI,                              // Device Type
    0x08000000,                          // Device Start Address (QSPI memory-mapped base)
    0x01000000,                          // Total Device Size (16 MB)

    1024,                                 // Page Size (256 bytes)
    0,                                   // Reserved
    0xFF,                                // Initial Content of Erased Memory
    50,                                  // Program Timeout (ms)
    4000,                                // Erase Timeout (ms)

    0x001000, 0x08000000,   // Sector size = 4 KB, start address
    SECTOR_END
};

#else /* AMEBAGREEN2_16MB */

struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,                      // Driver Version
    "GD25Q32 4MB External QSPI Flash",   // Device Name
    EXTSPI,                              // Device Type
    0x08000000,                          // Device Start Address (QSPI memory-mapped base)
    0x00400000,                          // Total Device Size (4 MB)

    256,                                 // Page Size (256 bytes)
    0,                                   // Reserved
    0xFF,                                // Initial Content of Erased Memory
    50,                                  // Program Timeout (ms)
    4000,                                // Erase Timeout (ms)

    0x001000, 0x08000000,                // Sector Size = 4 KB, Sector Start Address
    SECTOR_END                           // End of Sector List
};

#endif /* AMEBAGREEN2_16MB */

#elif defined(AMEBADPLUS) /* AMEBAGREEN2 */

/**
 * For AmebaDPlus RTL8721DCM
 */
__attribute__((section("DevDscr"))) struct FlashDevice const FlashDevice  =  {
    FLASH_DRV_VERS,
    "GD25Q64 8MB External QSPI Flash",
    EXTSPI,
    0x08000000,              // ? Correct Start Address (mapped QSPI region)
    0x00800000,              // 8 MB total size

    256,                     // Page size (GD25Q64 = 256 bytes)
    0,
    0xFF,
    50,                      // typical program timeout
    4000,                    // typical erase timeout

    0x001000, 0x08000000,    // ? 4 KB uniform sectors
    SECTOR_END
};

#endif /* AMEBADPLUS */

