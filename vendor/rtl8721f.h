#include "core_cm33_km4.h"

typedef struct {
	__IO uint32_t WDG_MKEYR ;  /*!< WDG MAGIC KEY REGISTER,  Address offset:0x000 */
	__IO uint32_t WDG_CR    ;  /*!< WDG CONTROL REGSIETR Register,  Address offset:0x004 */
	__IO uint32_t WDG_RLR   ;  /*!< WDG RELAOD REGISTER,  Address offset:0x008 */
	__IO uint32_t WDG_WINR  ;  /*!< WDG WINDOW REGISTER,  Address offset:0x00C */
	__IO uint32_t IWDG_DUMMY;  /*!< WDG DUMMY REGISTER,  Address offset:0x010 */
} WDG_TypeDef;

#define IWDG_REG_BASE                      0x4080AC00
#define IWDG_DEV                           ( ( WDG_TypeDef * ) ( IWDG_REG_BASE ) )

extern void BOOT_ROM_OSC131_Enable(void);
extern void BOOT_ROM_SPUFlash(void);
void BOOT_ROM_InitSpic(void);
void BOOT_ROM_ResetVsr(void);
extern uint8_t __rom_bss_start__[];
extern uint8_t __rom_bss_end__[];
extern uint8_t __rom_bss_start_s__[];
extern uint8_t __rom_bss_end_s__[];
