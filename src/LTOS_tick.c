//
// LTOS_tick.c
//
// Author: Levent TURA
//
//

#include "main.h"


__IO uint64_t tick = 0;


/**
  * @brief  Get tick count
  * @param	None
  * @retval None
  */
tick_t LTOS_getTick(void)
{
	tick_t preTick;

	while(preTick != tick) {
		preTick = tick;
	}

	return preTick;
}

/**
  * @brief  Init tick count
  * @param	None
  * @retval None
  */
void LTOS_tickInit(void)
{
	tick = 0;
}

/**
  * @brief  Increase tick count
  * @param	None
  * @retval None
  */
void LTOS_tickIncrease(void)
{
	tick++;
}

/**
  * @brief  Get tick us till now
  * @param	None
  * @retval us value till now @uint64_t
  */
uint64_t LTOS_tick2us(void)
{
#ifdef LTOS_TICK_RESOL_US
	return LTOS_getTick();
#else
	return (LTOS_getTick()/1000);
#endif
}

/**
  * @brief  Get tick ms till now
  * @param	None
  * @retval ms value till now @uint32_t
  */
uint64_t LTOS_tick2ms(void)
{
#ifdef LTOS_TICK_RESOL_US
	return LTOS_getTick()*1000;
#else
	return LTOS_getTick();
#endif
}
