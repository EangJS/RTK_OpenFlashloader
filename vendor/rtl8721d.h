/** @file rtl8721d.h
 *
 *  @brief This file contains all the register definitions and macros for the RTL8721DX
 *         required by the Flash loader.
 */

#include <stdint.h>
#include "core_cm33_km4.h"


/* ***************************************************************************/
/*    Watch Dog Timer (WDG)                                                 */
/* ***************************************************************************/

typedef struct {
    volatile uint32_t WDG_MKEYR;                                                                                    /*!< WDG MAGIC KEY REGISTER,  Address offset: 0x000 */
    volatile uint32_t WDG_CR;                                                                                       /*!< WDG CONTROL REGISTER,  Address offset: 0x004 */
    volatile uint32_t WDG_RLR;                                                                                      /*!< WDG RELOAD REGISTER,  Address offset: 0x008 */
    volatile uint32_t WDG_WINR;                                                                                     /*!< WDG WINDOW REGISTER,  Address offset: 0x00C */
    volatile uint32_t IWDG_DUMMY;                                                                                   /*!< WDG DUMMY REGISTER,  Address offset: 0x010 */
} WDG_TypeDef;

#define IWDG_REG_BASE            0x41008C00
#define IWDG_DEV			     ((WDG_TypeDef *) (IWDG_REG_BASE))
