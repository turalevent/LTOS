/*
 * Project Name 	: AsyncUartComm_prj
 * File Name		: async_comm
 * Description		: Asynchronous Communication
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
#include "string.h"

uint8_t ascTxBuf[MAX_ASC_XFER_LEN] = {0},
		ascRxBuf[MAX_ASC_XFER_LEN] = {0};

ascXferSt_t ascState = ASC_XFER_STATE_IDLE;

asc_rx_callback_t ascRxCb = NULL;

uint16_t ascRxCnt,
		 ascRxCtr;

oneshot_t *ascOS = NULL;
tick_t	 ascTout;

/**
  * @brief  init Async. Comm. module
  * @param  None
  * @retval None
  */
void initASC(void)
{
	LL_DMA_DisableStream(ASC_UA_DMA, ASC_UA_DMA_TX_STR);
	LL_DMA_ConfigAddresses(ASC_UA_DMA, ASC_UA_DMA_TX_STR, (uint32_t)ascTxBuf, LL_USART_DMA_GetRegAddr(ASC_USART), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_EnableIT_TC(ASC_UA_DMA, ASC_UA_DMA_TX_STR);
	LL_DMA_EnableStream(ASC_UA_DMA, ASC_UA_DMA_TX_STR);
	LL_USART_EnableDMAReq_TX(ASC_USART);

	ascOS = LTOS_oneshotAlloc();
	if(!ascOS) {
		while(1);
	}
}

/**
  * @brief	send uint8_t buffer
  * @param  ptx : send buffer address
  * 		len	: length
  * @retval Async. comm. Xfer result
  * 		ASC_XFER_SUCCESS : Success
  * 		ASC_XFER_TX_LEN_ERR : Transmit legth exceed max length
  * 		ASC_XFER_TX_BUSY_ERR: Transmit is busy now..
  */
ascXferRes_t ASC_tx(uint8_t *ptx, uint32_t len)
{
	if( (len > MAX_ASC_XFER_LEN) || (!len) ) {
		return ASC_XFER_TX_LEN_ERR;
	}
	if(ascState&ASC_XFER_STATE_TX) {
		return ASC_XFER_TX_BUSY_ERR;
	}

	ascState |= ASC_XFER_STATE_TX;

	memcpy(ascTxBuf, ptx, sizeof(uint8_t)*len);

	LL_DMA_DisableStream(ASC_UA_DMA, ASC_UA_DMA_TX_STR);
	LL_DMA_SetDataLength(ASC_UA_DMA, ASC_UA_DMA_TX_STR, len);
	LL_DMA_EnableStream(ASC_UA_DMA, ASC_UA_DMA_TX_STR);

	return ASC_XFER_SUCCESS;
}

/**
  * @brief	Attach rx callback will be called after requested byte received
  * @param  cb  : callback address to be called when requested bytes received
  * 		len : requested received byte length
  * 		tm  : time in ms to call recall function after requested bytes received
  * @retval Async. comm. Xfer result
  * 		ASC_XFER_SUCCESS : Success
  * 		ASC_XFER_RX_CALLBACK_ERR : rx callback address is NULL
  * 		ASC_XFER_RX_BUSY_ERR : ASC receiving now..
  */
ascXferRes_t ASC_rx(asc_rx_callback_t cb, uint32_t len, uint32_t tm)
{
	if( (len > MAX_ASC_XFER_LEN) || (!len) ) {
		return ASC_XFER_RX_LEN_ERR;
	}
	if(cb == NULL) {
		return ASC_XFER_RX_CALLBACK_ERR;
	}
	if(ascState&ASC_XFER_STATE_RX) {
		return ASC_XFER_RX_BUSY_ERR;
	}

	ascRxCb = cb;
	ascRxCnt= len;
	ascTout = tm;

	ascState |= ASC_XFER_STATE_RX;

	return ASC_XFER_SUCCESS;
}

/**
  * @brief  Asny. Comm. Task
  * @param	argument
  * @retval None
  */
void ascTASK(uint32_t arg)
{
	ascRxCb(ascRxBuf, ascRxCnt);
	ascRxCb = NULL;
	ascRxCnt = 0;
	ascState &= ~ASC_XFER_STATE_RX;
}

/**
  * @brief  ASC TX-DMA Transfer Complete Interrupt Handler
  * @note   This function will be called by Interrupt Service..
  * @param  None
  * @retval None
  */
void ASC_TXDMA_IRQHandler()
{
	LL_DMA_ClearFlag_TC6(ASC_UA_DMA);

	ascState &= ~ASC_XFER_STATE_TX;
}

/**
  * @brief  ASC UX-RX Complete Interrupt Handler
  * @note   This function will be called by Interrupt Service..
  * @param  None
  * @retval None
  */
void ASC_UARX_IRQHandler()
{
	uint8_t rx;

	rx = LL_USART_ReceiveData8(ASC_USART);

	if(ascRxCnt == 0) {
		return;
	}

	ascRxBuf[ascRxCtr++] = rx;

	if(ascRxCtr == ascRxCnt) {
		if(ascRxCb != NULL) {
			LTOS_oneshotAttach(ascOS, (os_callback_t)ascTASK, 0, ascTout);
		}
		ascRxCtr = 0;
	}
}
