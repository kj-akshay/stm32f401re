/*
 * stm32f401xx_usart_driver.c
 *
 *  Created on: Nov 6, 2025
 *      Author: aksha
 */
#include "stm32f401xx_usart_driver.h"

/*********************************************************************************************************
 * @brief
 *
 * @param pUSARTx
 * @param EnOrDi
 *********************************************************************************************************/
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pUSARTx == USART1) USART1_PCLK_EN();
		else if (pUSARTx == USART2) USART2_PCLK_EN();
		else if (pUSARTx == USART6) USART6_PCLK_EN();
	}
	else
	{
		if(pUSARTx == USART1) USART1_PCLK_DI();
		else if (pUSARTx == USART2) USART2_PCLK_DI();
		else if (pUSARTx == USART6) USART6_PCLK_DI();
	}
}

void USART_Init(USART_Handle_t *pUSART_Handle);
void USART_DeInit(USART_RegDef_t *pUSARTx);
//Data Send and receive
void USART_SendData(USART_RegDef_t *pUSARTx, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_RegDef_t *pUSARTx, uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t Len);


//Other peripheral control API
/**********************************************************************************************************
 * @brief
 *
 * @param pUSARTx
 * @param EnOrDi
 *********************************************************************************************************/
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pUSARTx->CR1 |= 1 << 13;
	}
	else
	{
		pUSARTx->CR1 &= ~(1 << 13);
	}
}


/**********************************************************************************************************
 * @brief
 *
 * @param pUSARTx
 * @param StatusFlagName
 * @return
 *********************************************************************************************************/
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{

}



void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);

//IRQ configuration and ISR Handling
void USART_IRQInterrruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pUSART_Handle);

//Application callback
void USART_ApplicationEventCallback(USART_Handle_t *pUSART_Handle, uint8_t AppEvent);



