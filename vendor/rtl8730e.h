#include "core_cm33_km4.h"

typedef struct {
	__IO uint32_t WDG_MKEYR;  /*!< WDG MAGIC KEY REGISTER,  Address offset:0x000 */
	__IO uint32_t WDG_CR   ;  /*!< WDG CONTROL REGSIETR Register,  Address offset:0x004 */
	__IO uint32_t WDG_RLR  ;  /*!< WDG RELAOD REGISTER,  Address offset:0x008 */
	__IO uint32_t WDG_WINR ;  /*!< WDG WINDOW REGISTER,  Address offset:0x00C */
} WDG_TypeDef;
#define IWDG_REG_BASE                      0x42008400
#define IWDG_DEV                           ( ( WDG_TypeDef * ) ( IWDG_REG_BASE ) )

_LONG_CALL_ uint32_t SYSCFG_BootFromNor(void);
