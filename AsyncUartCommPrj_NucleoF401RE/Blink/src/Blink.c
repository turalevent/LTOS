//
// Blink.c
//
// Author: Levent TURA
//
//

#include "main.h"



uint8_t blinkFlag;
oneshot_t *blinkOS;

/**
  * @brief  Init Blink Task
  * @param	None
  * @retval None
  */
void BlinkInit(void)
{
	blinkFlag = 0;

	blinkOS = LTOS_oneshotAlloc();
	if(blinkOS) {
		LTOS_oneshotAttach(blinkOS, (os_callback_t)BlinkTASK, 0, BLINK_OFF_TIME);
	}
}

/**
  * @brief  Blink Task
  * @param	argument
  * @retval None
  */
void BlinkTASK(uint32_t arg)
{
	tick_t tout;

	blinkFlag ^= 1;

	if(blinkFlag) {
		LL_GPIO_SetOutputPin(BLINK_LED_GPIO_Port, BLINK_LED_Pin);
		tout = BLINK_ON_TIME;
	} else {
		LL_GPIO_ResetOutputPin(BLINK_LED_GPIO_Port, BLINK_LED_Pin);
		tout = BLINK_OFF_TIME;
	}

	LTOS_oneshotAttach(blinkOS, (os_callback_t)BlinkTASK, 0, tout);
}
