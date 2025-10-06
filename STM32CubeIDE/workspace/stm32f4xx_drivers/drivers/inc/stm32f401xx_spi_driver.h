/*
 * stm32f401xx_spi_driver.h
 *
 *  Created on: Oct 5, 2025
 *      Author: aksha
 */

#ifndef INC_STM32F401XX_SPI_DRIVER_H_
#define INC_STM32F401XX_SPI_DRIVER_H_

#include "stm32f401xx.h"

/**
 * configuration structure for spi peripheral
 *
 */
typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

/**
 * Handle structure for SPI peripheral
 *
 */
typedef struct{
	SPI_RegDef_t *pSPIx;  //This holds the base address of the SPIx
	SPI_Config_t SPIConfig;
}SPI_Handle_t;


/*****************************************************************************************************
 * 						API Supported by this driver
 *****************************************************************************************************/

/**
 * peripheacal clk setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi);


/**
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/**
 * Data send and receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer,uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer,uint32_t Len);


/**
 * IRQ config and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);


/**
 * SPI_DeviceMode
 * SPI_CRI[2]
 */
#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0


/**
 * SPI_BusConfig
 * SPI_CR1 bit 15 and 14 and 10
 */
#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3

/**
 * SPI_SclkSpeed
 * peripheral clock is 16Mhz if HSI is used
 * SPI_CR1[5:3]
 */
#define SPI_SCLK_SPEED_DIV2			0
#define SPI_SCLK_SPEED_DIV4			1
#define SPI_SCLK_SPEED_DIV8			2
#define SPI_SCLK_SPEED_DIV16		3
#define SPI_SCLK_SPEED_DIV32		4
#define SPI_SCLK_SPEED_DIV64		5
#define SPI_SCLK_SPEED_DIV128		6
#define SPI_SCLK_SPEED_DIV256		7

/**
 * SPI_DFF
 * SPI_CR1[11]
 */
#define SPI_DFF_8BITS		0
#define SPI_DFF_16BITS		1

/**
 * SPI_CPOL
 */
#define SPI_CPOL_HIGH		1
#define SPI_CPOL_LOW		0

/**
 * SPI_CPHA
 */
#define SPI_CPHA_HIGH		1
#define SPI_CPHA_LOW		0

 /**
  * SPI_SSM
  */
#define SPI_SSM_EN		1
#define SPI_SSM_DI		0
#endif /* INC_STM32F401XX_SPI_DRIVER_H_ */
