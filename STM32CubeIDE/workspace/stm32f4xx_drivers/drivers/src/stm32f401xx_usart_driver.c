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


/**********************************************************************************************************
 * @brief
 *
 * @param pUSART_Handle
 *********************************************************************************************************/
void USART_Init(USART_Handle_t *pUSART_Handle)
{

	//Temp var
	uint32_t tempreg=0;

/******************************** Configuration of CR1******************************************/

	//enable the Clock
	USART_PeriClockControl(pUSART_Handle->pUSARTx, ENABLE);

	//Enable USART Tx and Rx 
	if ( pUSART_Handle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		//enable the Receiver bit field
		tempreg|= (1 << USART_CR1_RE);
	}else if (pUSART_Handle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		//enable the Transmitter bit field
		tempreg |= ( 1 << USART_CR1_TE );

	}else if (pUSART_Handle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		//enable the both Transmitter and Receiver bit fields
		tempreg |= ( ( 1 << USART_CR1_RE) | ( 1 << USART_CR1_TE) );
	}

    //configure the Word length
	tempreg |= pUSART_Handle->USART_Config.USART_WordLength << USART_CR1_M;


    //parity control bit fields
	if ( pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
	{
		//enale the parity control
		tempreg |= ( 1 << USART_CR1_PCE);

		//default EVEN parity will be selected once you enable the parity control

	}else if (pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD )
	{
		//enable the parity control
	    tempreg |= ( 1 << USART_CR1_PCE);

	    //enable ODD parity
	    tempreg |= ( 1 << USART_CR1_PS);

	}

   //Program the CR1 register
	pUSART_Handle->pUSARTx->CR1 = tempreg;

/******************************** Configuration of CR2******************************************/

	tempreg=0;

	//configure the number of stop bits
	tempreg |= pUSART_Handle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

	//Program the CR2 register
	pUSART_Handle->pUSARTx->CR2 = tempreg;

/******************************** Configuration of CR3******************************************/

	tempreg=0;

	//hardware flow control
	if ( pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		//enable CTS flow control
		tempreg |= ( 1 << USART_CR3_CTSE);


	}else if (pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		//enable RTS flow control
		tempreg |= (1 << USART_CR3_RTSE);

	}else if (pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		//enable both CTS and RTS Flow control
		tempreg |= ( 1 << USART_CR3_CTSE);
		tempreg |= ( 1 << USART_CR3_RTSE);
	}


	pUSART_Handle->pUSARTx->CR3 = tempreg;

/******************************** Configuration of BRR(Baudrate register)******************************************/

	//configure the baud rate
}



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
	if(pUSARTx->SR & StatusFlagName) return FLAG_SET;
	else return FLAG_RESET;
}


/**********************************************************************************************************
 * @brief
 *
 * @param pUSARTx
 * @param StatusFlagName
 *********************************************************************************************************/
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName){

}

//IRQ configuration and ISR Handling
void USART_IRQInterrruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pUSART_Handle);

//Application callback
void USART_ApplicationEventCallback(USART_Handle_t *pUSART_Handle, uint8_t AppEvent);



