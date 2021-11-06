/*
 * Project Name 	: AsyncUartComm_prj
 * File Name		: demo
 * Description		: Demo application for Asynchronous Communication
 * Writer Name		: Levent TURA
 * Modifier Name	: ---
 * Version Number  	: 0.01
 * Version History	:
 *                	  0.01 ------------------------------------------------------------
 *                	   - First version release
 *                	  0.02 ------------------------------------------------------------
 *
 * */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

char demoTxBuf[] = "ASYNC-USART COMMUNICATION DEMO\r\n";
char demoRxBuf[DEMO_MAX_RX_SIZE];

oneshot_t *demoOS = NULL;

/**
  * @brief  init Async. Comm. module
  * @param  None
  * @retval None
  */
void initDEMO(void)
{
	demoOS = LTOS_oneshotAlloc();
	if(demoOS) {
		LTOS_oneshotAttach(demoOS, (os_callback_t)DemoTASK, 0, DEMO_PER_TIME);
	}

	ASC_rx(DemoASCCallback, DEMO_MAX_RX_SIZE, _1ms);
}

/**
  * @brief  Demo Task
  * @param	argument
  * @retval None
  */
void DemoTASK(uint32_t arg)
{
	ASC_tx((uint8_t *)demoTxBuf, sizeof(demoTxBuf)-1);

	LTOS_oneshotAttach(demoOS, (os_callback_t)DemoTASK, 0, DEMO_PER_TIME);
}

/**
  * @brief  Demo Async-USART Communication (ASC) Receive callback
  * @note	This function will be called by ASC
  * @param	pRx	: Received buffer's pointer
  * 		len	: Received byte length
  * @retval None
  */
void DemoASCCallback(uint8_t *pRx, uint8_t len)
{
	if(len > DEMO_MAX_RX_SIZE) {
		return;
	}

	memcpy(demoRxBuf, pRx, sizeof(uint8_t)*len);

	ASC_tx((uint8_t *)demoRxBuf, len);
}
