/*
 * stm32f401xx_spi_driver.c
 *
 *  Created on: Oct 5, 2025
 *      Author: aksha
 */
#include "stm32f401xx_spi_driver.h"

/**
 * @brief
 *
 * @param pSPIx
 * @param EnorDi
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pSPIx == SPI1) SPI1_PCLK_EN();
		else if (pSPIx == SPI2) SPI2_PCLK_EN();
		else if (pSPIx == SPI3) SPI3_PCLK_EN();
		else if (pSPIx == SPI4) SPI4_PCLK_EN();
	}
	else{
		if (pSPIx == SPI1) SPI1_PCLK_DI();
		else if (pSPIx == SPI2) SPI2_PCLK_DI();
		else if (pSPIx == SPI3) SPI3_PCLK_DI();
		else if (pSPIx == SPI4) SPI4_PCLK_DI();
	}
}


/**
 * @brief
 *
 * @param pSPIHandle
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//config CR1 reg

	uint32_t tempreg = 0;
	//1. config the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR ;

	//2. configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//BIDI mode should be cleared
		tempreg &= ~(1 << SPI_CR1_BIDI_MODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD )
	{
		//BIDI mode should be set
		tempreg |= (1 << SPI_CR1_BIDI_MODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//BIDI mode should be cleared
		tempreg &= ~(1 << SPI_CR1_BIDI_MODE);
		//RXONLY bit must be set
		tempreg |= (1 << SPI_CR1_RX_ONLY);
	}

	//3.configure the spi serail clock speed
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//4.configure the DFF
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	//5.Configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	//6.Configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	pSPIHandle->pSPIx->CR1 = tempreg;
}


/**
 * @brief
 *Use RCC reset register to deinit
 * @param pSPIx
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

}

/**
 * @brief
 *
 * @param pSPIx
 * @param pTxBuffer
 * @param Len
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer,uint32_t Len)
{

}

/**
 * @brief
 *
 * @param pSPIx
 * @param pRxBuffer
 * @param Len
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer,uint32_t Len)
{

}


/**
 * @brief
 *
 * @param IRQNumber
 * @param EnorDi
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi)
{

}


/**
 * @brief
 *
 * @param IRQNumber
 * @param IRQPriority
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority)
{

}


/**
 * @brief
 *
 * @param pSPIHandle
 */
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{

}

