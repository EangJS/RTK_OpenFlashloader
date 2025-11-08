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
