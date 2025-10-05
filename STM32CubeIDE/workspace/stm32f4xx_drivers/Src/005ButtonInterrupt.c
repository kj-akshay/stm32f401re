/*
 * 005ButtonInterrupt.c
 *
 *  Created on: Sep 28, 2025
 *      Author: aksha
 */


/**
 * @brief Program to toggle the on board LED whenever the on board push button is presses
 *
 */
#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"

#define HIGH 1
#define LOW		0
#define BTN_PRESSED LOW


void delay(void){
	for(uint32_t i=0;i<500000/2;i++);
}


int main()
{
	GPIO_Handle_t GpioLed,GpioBtn;

	GpioLed.pGPIOx= GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_HIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PP;
	//GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_OD;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&GpioLed);


	GpioBtn.pGPIOx= GPIOC;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RFT;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_HIGH;
	//GpioBtn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PP;  // no required when pin mode is INPUT
		//GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_OD;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOC, ENABLE);
	GPIO_Init(&GpioBtn);

	//IRQ configurations
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10,NVIC_IRQ_PRIO15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
	while(1);



	return 0;
}

void EXTI15_10_IRQHandler(void){
	GPIO_IRQHandling(GPIO_PIN_NO_13);
	ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
	//delay();

}
