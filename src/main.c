#include "stdint.h"
#include "stm32f407xx.h"
#include "System.h"
#include "SPI.h"
#include "Uart.h"


int main(void)
{
		SystemInit168MHZ();
		SpiInit();
		Uart2Init();

		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
		GPIOD->MODER |= GPIO_MODER_MODER14_0;
		GPIOD->MODER &= ~GPIO_MODER_MODER14_1;

		GPIOD->ODR |= GPIO_ODR_ODR_14;

		while(1)
			{


			}
}
