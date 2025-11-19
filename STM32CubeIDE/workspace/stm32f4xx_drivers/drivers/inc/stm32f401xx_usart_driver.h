/*
 * stm32f401xx_usart_driver.h
 *
 *  Created on: Nov 6, 2025
 *      Author: aksha
 */

#ifndef INC_STM32F401XX_USART_DRIVER_H_
#define INC_STM32F401XX_USART_DRIVER_H_

#include "stm32f401xx.h"


/**
 * USART related status flag
 *
 */
#define SPI_TXE_FLAG		(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG		(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG		(1 << SPI_SR_BSY)

/*
 *@USART_Mode
 *Possible options for USART_Mode
 *Register-CR1  Bit - 2 and 3
 */
#define USART_MODE_ONLY_TX		0
#define USART_MODE_ONLY_RX 		1
#define USART_MODE_TXRX  		2


/*
 *@USART_Baud
 *Possible options for USART_Baud
 *Register-BRR
 */
#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					2400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define SUART_STD_BAUD_3M 					3000000


/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 *Register-CR1  Bit - 9 and 10
 */
#define USART_PARITY_DISABLE  0
#define USART_PARITY_EN_EVEN  1
#define USART_PARITY_EN_ODD   2

/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 *Register-CR1  Bit - 12
 */
#define USART_WORDLEN_8BITS  0
#define USART_WORDLEN_9BITS  1

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
#define USART_STOPBITS_1     0
#define USART_STOPBITS_0_5   1
#define USART_STOPBITS_2     2

/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3




/**
 * config structure fir uart peripheral
 */
typedef struct{
	uint8_t USART_Mode;
	uint8_t USART_Baud;
	uint8_t USART_NoOfStopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
}USART_Config_t;

/**
 * Handle structure for USART peripheral
 *
 */
typedef struct{
	USART_RegDef_t *pUSARTx;  //This holds the base address of the SPIx
	USART_Config_t USART_Config;
}USART_Handle_t;



/*****************************************************************************************************
 * 						API Supported by this USART driver
 *****************************************************************************************************/
/**
 * peripheacal clk setup
 *

 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);

void USART_Init(USART_Handle_t *pUSART_Handle);
void USART_DeInit(USART_RegDef_t *pUSARTx);
//Data Send and receive
void USART_SendData(USART_RegDef_t *pUSARTx, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_RegDef_t *pUSARTx, uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t Len);


//Other peripheral control API
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName);
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);

//IRQ configuration and ISR Handling
void USART_IRQInterrruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pUSART_Handle);

//Application callback
void USART_ApplicationEventCallback(USART_Handle_t *pUSART_Handle, uint8_t AppEvent);



#endif /* INC_STM32F401XX_USART_DRIVER_H_ */

