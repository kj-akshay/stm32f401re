/*
 * 007spi_txonly_arduino.c
 *
 *  Created on: Oct 12, 2025
 *      Author: aksha
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


void delay(void){
	for(uint32_t i=0;i<500000/2;i++);
}

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
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);
}

void SPI2_Inits()
{
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV128;
	SPI2handle.SPIConfig.SPI_DFF =  SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

	SPI_Init(&SPI2handle);
}

void GPIO_ButtonInit(void){
	GPIO_Handle_t GpioBtn;
	GpioBtn.pGPIOx= GPIOC;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_HIGH;
	//GpioBtn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PP;  // no required when pin mode is INPUT
		//GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_OD;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//GPIO_PeriClockControl(GPIOC, ENABLE);
	GPIO_Init(&GpioBtn);
}


int main()
{
	char user_data[] = "Hello World";


	GPIO_ButtonInit();

	//this is to initialize the GPIO to behave as SPI
	SPI2_GPIOInits();

	// the function is used to initialize the SPI2 peripheral parameter
	SPI2_Inits();

	//this makes NSS signal internally high and avoids MODF error
	//SPI_SSICofig(SPI2, ENABLE);

	/**
	 * making SSOE 1 does NSS optput enable
	 * The NSS pin is automatically managed by HW
	 * i.e when SPE=1 ,NSS will be pulled to low
	 * and NSS pin will be high when SPE=0;
	 */
	SPI_SSOECofig(SPI2, ENABLE);

	while(1)
	{
		while( GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) ); // wait until pressed (active low)


		//delay();

			//SPi peripheral has to be enabled before the transmission/receive of the data
		SPI_PeripheralControl(SPI2, ENABLE);

		//first send length in
		uint8_t dataLen = strlen(user_data);
		SPI_SendData(SPI2, &dataLen, 1);

		SPI_SendData(SPI2,(uint8_t*)user_data, strlen(user_data));


		 //lets confirm SPI busy fkag
		 while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

		 SPI_PeripheralControl(SPI2, DISABLE);


		 // Wait until button released (so only one message per press)
		 //while( !GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) )
		 delay();



	//while(1);
	}



	return 0;

}


