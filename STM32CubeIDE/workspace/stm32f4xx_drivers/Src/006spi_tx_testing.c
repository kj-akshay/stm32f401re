/*
 * 006spi_tx_testing.c
 *
 *  Created on: Oct 6, 2025
 *      Author: aksha
 *
 *  @Exercise :
 *  	1.test the SPI_sendData API to send the string "Hello World" and use the following configuration;
 *  		1.SPI-2 master mode
 *  		2. SCLK max possible
 *  		3. DFF=0 and DFF=1

 */
/**
 * *  	Inference :
 *  		required pin: MOSi, MISo(not required but can be configured),SCLK,NSS not required
 *  		MOSI and SCLK (must required)
 *
 *  		Alternate functionality 05 from ref manual
 *  		PB15 -> MOSI for SPI2
 *  		PB14 MISO for SPI2
 *  		PB13 SPI2_SCLK
 *  		PB12 SPI2_NSS
 */
#include <stdlib.h>
#include <string.h>

#include "stm32f401xx.h"
#include "stm32f401xx_spi_driver.h"
#include "stm32f401xx_gpio_driver.h"

void SPI2_GPIOInits()
{
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunction = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_HIGH;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPIPins);

	//NSS
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	//GPIO_Init(&SPIPins);
}

void SPI2_Inits()
{
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
	SPI2handle.SPIConfig.SPI_DFF =  SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN;

	SPI_Init(&SPI2handle);
}

int main()
{
	char user_data[] = "Hello World";
	//this is to initialize the GPIO to behave as SPI
	SPI2_GPIOInits();

	// the function is used to initialize the SPI2 peripheral parameter
	SPI2_Inits();

	//this makes NSS signal internally high and avoids MODF error
	SPI_SSICofig(SPI2, ENABLE);

	//SPi peripheral has to be enabled before the transmission/receive of the data
	SPI_PeripheralControl(SPI2, ENABLE);

 	SPI_SendData(SPI2,(uint8_t*)user_data, strlen(user_data));

 	 //lets confirm SPI busy fkag
 	while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

 	SPI_PeripheralControl(SPI2, DISABLE);

	while(1);



	return 0;

}

