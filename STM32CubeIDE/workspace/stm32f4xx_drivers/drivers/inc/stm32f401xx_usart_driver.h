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
	SPI_RegDef_t *pUSARTx;  //This holds the base address of the SPIx
	SPI_Config_t USART_Config;
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

