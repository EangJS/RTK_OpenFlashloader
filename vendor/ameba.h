#include <stddef.h>

#if AMEBADPLUS
    #include "rtl8721d.h"
#elif AMEBAGREEN2
    #include "rtl8721f.h"
#elif AMEBASMART
	#include "rtl8730e.h"
#else
	#error "No valid device defined!"
#endif /* AMEBADPLUS */

/** @defgroup FLASH_Erase_Type
  * @{
  */
#define ERASE_CHIP              0
#define ERASE_BLOCK             1
#define ERASE_SECTOR            2

static inline void __ISB(void) {
    __asm volatile("isb 0xF" ::: "memory");
}

static inline void __DSB(void) {
    __asm volatile("dsb 0xF" ::: "memory");
}

static inline void SCB_DisableDCache(void)
{
#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
	register uint32_t ccsidr;
	register uint32_t sets;
	register uint32_t ways;

	SCB->CSSELR = 0U; /*(0U << 1U) | 0U;*/  /* Level 1 data cache */
	__DSB();

	SCB->CCR &= ~(uint32_t)SCB_CCR_DC_Msk;  /* disable D-Cache */
	__DSB();

	ccsidr = SCB->CCSIDR;

	/* clean & invalidate D-Cache */
	sets = (uint32_t)(CCSIDR_SETS(ccsidr));
	do {
		ways = (uint32_t)(CCSIDR_WAYS(ccsidr));
		do {
			SCB->DCCISW = (((sets << SCB_DCCISW_SET_Pos) & SCB_DCCISW_SET_Msk) |
						   ((ways << SCB_DCCISW_WAY_Pos) & SCB_DCCISW_WAY_Msk));
#if defined ( __CC_ARM )
			__schedule_barrier();
#endif /* __CC_ARM */
		} while (ways-- != 0U);
	} while (sets-- != 0U);

	__DSB();
	__ISB();
#endif /* defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U) */
}

_LONG_CALL_ void FLASH_Erase(uint32_t EraseType, uint32_t Address);
_LONG_CALL_ void FLASH_TxData(uint32_t StartAddr, uint32_t DataPhaseLen, uint8_t *pData);
_LONG_CALL_ void RCC_PeriphClockSource_SPIC(uint32_t Source);
_LONG_CALL_ void FLASH_Read_HandShake_Cmd(uint32_t Dphy_Dly_Cnt, uint32_t NewState);
_LONG_CALL_ void FLASH_DeepPowerDown(uint32_t NewState);
_LONG_CALL_ void WDG_Refresh(WDG_TypeDef *WDG);
_LONG_CALL_ void _memcpy(void *dst, void *src, uint32_t sz);
_LONG_CALL_ void *_memset(void *s, int c, size_t n);

static void Flash_Write_Lock_IPC(uint8_t sync_type);
