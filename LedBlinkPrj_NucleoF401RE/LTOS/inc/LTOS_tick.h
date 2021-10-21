//
// LTOS_tick.h
//
// Author: Levent TURA
//
//

#ifndef __LTOS_TICK_H
#define __LTOS_TICK_H

#include "LTOS_config.h"

#ifdef LTOS_TICK_RESOL_US

#define _1us			(uint64_t)(1)
#define _3us			(uint64_t)(3*_1us)
#define _10us			(uint64_t)(10*_1us)
#define _50us			(uint64_t)(50*_1us)
#define _100us			(uint64_t)(100*_1us)
#define _1ms			(uint64_t)(1000)

#else

#define _1ms			(uint64_t)(1)

#endif

#define _2ms			(uint64_t)(2*_1ms)
#define _5ms			(uint64_t)(5*_1ms)
#define _6ms			(uint64_t)(6*_1ms)
#define _10ms			(uint64_t)(10*_1ms)
#define _20ms			(uint64_t)(20*_1ms)
#define _30ms			(uint64_t)(30*_1ms)
#define _40ms			(uint64_t)(40*_1ms)
#define _50ms			(uint64_t)(50*_1ms)
#define _75ms			(uint64_t)(75*_1ms)
#define _100ms			(uint64_t)(100*_1ms)
#define _125ms			(uint64_t)(125*_1ms)
#define _200ms			(uint64_t)(200*_1ms)
#define _250ms			(uint64_t)(250*_1ms)
#define _500ms			(uint64_t)(500*_1ms)
#define _800ms			(uint64_t)(800*_1ms)
#define _900ms			(uint64_t)(900*_1ms)
#define _1sec			(uint64_t)(1000*_1ms)
#define _2sec			(uint64_t)(2*_1sec)
#define _3sec			(uint64_t)(3*_1sec)
#define _5sec			(uint64_t)(5*_1sec)
#define _1min			(uint64_t)(60*_1sec)

#define _1hr			(uint64_t)(60*_1min)

typedef uint64_t tick_t;

/**
  * @brief  Get tick count
  * @param	None
  * @retval tick value untill now
  */
tick_t LTOS_getTick(void);

/**
  * @brief  Increase tick count
  * @param	None
  * @retval None
  */
void LTOS_tickIncrease(void);

/**
  * @brief  Get tick us till now
  * @param	None
  * @retval us value till now
  */
uint64_t LTOS_tick2us(void);

/**
  * @brief  Get tick ms till now
  * @param	None
  * @retval ms value till now
  */
uint64_t LTOS_tick2ms(void);

#endif	// __TICK_H
