/*
 * stm32f401xx.h
 *
 *  Created on: Sep 11, 2025
 *      Author: aksha
 */

#ifndef INC_STM32F401XX_H_
#define INC_STM32F401XX_H_
/*
Base addrress of Falsh and Sram memory
*/
#define FLASH_BASEADDR	0x08000000U		//reference manual page 45
#define SRAM_BASEADDR	0x20000000U		//reference manual page 42
#define ROM_BASEADDR	0x1FFF0000U		//reference manual page 45 rom is also called system memory

/*
Base addrress of bus domains
*/
#define APB1PERIPH_BASE    0x40000000U      //0x4000 0000 - 0x4000 73FF    
#define APB2PERIPH_BASE    0x40010000U     // 0x4001 0000 - 0x4001 4BFF
#define AHB1PERIPH_BASE    0x40020000U      //0x4002 0000 - 0x4002 67FF
#define AHB2PERIPH_BASE    0x50000000U      //0x5000 0000 - 0x5003 FFFF


/*
Base address of peripherals which are hanging on AHB1 bus
(GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOH,DMA1,DMA2,Flash interface register,RCC,CRC) page 38 of reference manual
*/
#define GPIOA_BASEADDR  (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR  (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR  (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR  (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR  (AHB1PERIPH_BASE + 0x1000)
#define GPIOH_BASEADDR  (AHB1PERIPH_BASE + 0x1C00)      


/*
Base address of peripherals which are hanging on APB1 bus
(TIM2,3,4,5,RTC,WWDG,SPI2,SPI3,USART2,I2C1,2,3,) page 38 of reference manual
*/
#define I2C1_BASEADDR   (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR   (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR   (APB1PERIPH_BASE + 0x5C00)
#define SPI2_BASEADDR   (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR   (APB1PERIPH_BASE + 0x3C00)
#define USART2_BASEADDR (APB1PERIPH_BASE + 0x4400)




#endif /* INC_STM32F401XX_H_ */
