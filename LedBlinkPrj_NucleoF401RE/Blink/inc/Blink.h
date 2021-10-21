//
// Blink.h
//
// Author: Levent TURA
//
//

#ifndef __BLINK_H
#define __BLINK_H

#define BLINK_ON_TIME	(uint64_t)(_100ms)
#define BLINK_OFF_TIME	(uint64_t)(_1sec+_900ms)

/**
  * @brief  Init Blink Task
  * @param	None
  * @retval None
  */
void BlinkInit(void);

/**
  * @brief  Blink Task
  * @param	argument
  * @retval None
  */
void BlinkTASK(uint32_t arg);

#endif	// __BLINK_H
