#ifndef __DEMO_H__
#define __DEMO_H__

#ifdef __cplusplus
 extern "C" {
#endif

#define DEMO_MAX_RX_SIZE 	5
#define DEMO_PER_TIME		_5sec

/**
  * @brief  init Async. Comm. module
  * @param  None
  * @retval None
  */
void initDEMO(void);

/**
  * @brief  Demo Task
  * @param	argument
  * @retval None
  */
void DemoTASK(uint32_t arg);

/**
  * @brief  Demo Async-USART Communication (ASC) Receive callback
  * @note	This function will be called by ASC
  * @param	pRx	: Received buffer's pointer
  * 		len	: Received byte length
  * @retval None
  */
void DemoASCCallback(uint8_t *pRx, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_H__ */
