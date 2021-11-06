#ifndef __ASYNC_COMM_H__
#define __ASYNC_COMM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#define MAX_ASC_XFER_LEN	300

#define ASC_USART			USART2
#define ASC_UA_DMA			DMA1
#define ASC_UA_DMA_TX_STR	LL_DMA_STREAM_6
#define ASC_UA_DMA_RX_STR	LL_DMA_STREAM_5

enum ascStates {
	ASC_XFER_STATE_IDLE 	= 0x00,
	ASC_XFER_STATE_TX		= 0x01,
	ASC_XFER_STATE_RX		= 0x02,
	ASC_XFER_STATE_RX_ERROR = 0x04
};
typedef enum ascStates ascXferSt_t;

enum ascXferRes {
	ASC_XFER_SUCCESS,
	ASC_XFER_TX_LEN_ERR,
	ASC_XFER_RX_LEN_ERR,
	ASC_XFER_TX_BUSY_ERR,
	ASC_XFER_RX_BUSY_ERR,
	ASC_XFER_RX_CALLBACK_ERR
};
typedef enum ascXferRes ascXferRes_t;

typedef void (*asc_rx_callback_t)(uint8_t *, uint8_t);

/**
  * @brief  init Async. Comm. module
  * @param  None
  * @retval None
  */
void initASC(void);

/**
  * @brief	send uint8_t buffer
  * @param  ptx : send buffer address
  * 		len	: length
  * @retval Async. comm. Xfer result
  * 		ASC_XFER_SUCCESS : Success
  * 		ASC_XFER_TX_LEN_ERR : Transmit legth exceed max length
  * 		ASC_XFER_TX_BUSY_ERR: Transmit is busy now..
  */
ascXferRes_t ASC_tx(uint8_t *ptx, uint32_t len);

/**
  * @brief	Attach rx callback will be called after requested byte received
  * @param  pRxCallback : callback address to be called when requested bytes received
  * 		len : requested received byte length
  * 		tm  : time in ms to call recall function after requested bytes received
  * @retval Async. comm. Xfer result
  * 		ASC_XFER_SUCCESS : Success
  * 		ASC_XFER_RX_CALLBACK_ERR : rx callback address is NULL
  * 		ASC_XFER_RX_BUSY_ERR : ASC receiving now..
  */
ascXferRes_t ASC_rx(asc_rx_callback_t pRxCallback, uint32_t len, uint32_t tm);

/**
  * @brief  Asny. Comm. Task
  * @param	argument
  * @retval None
  */
void ascTASK(uint32_t arg);

/**
  * @brief  ASC TX-DMA Transfer Complete Interrupt Handler
  * @note   This function will be called by Interrupt Service..
  * @param  None
  * @retval None
  */
void ASC_TXDMA_IRQHandler();

/**
  * @brief  ASC UX-RX Complete Interrupt Handler
  * @note   This function will be called by Interrupt Service..
  * @param  None
  * @retval None
  */
void ASC_UARX_IRQHandler();

#ifdef __cplusplus
}
#endif

#endif /* __ASYNC_COMM_H__ */
