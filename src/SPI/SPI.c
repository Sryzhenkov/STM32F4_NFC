#include "SPI.h"

void SpiInit(void)
{	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	
	GPIOA->MODER |=  GPIO_MODER_MODER4_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER4_1;
	GPIOA->ODR	 &=  ~GPIO_ODR_ODR_4;
	
	GPIOA->MODER  |=  (GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);
	GPIOA->MODER  &= ~(GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);
	GPIOA->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL5_Pos) | (0x05 << GPIO_AFRL_AFSEL6_Pos) | (0x05 << GPIO_AFRL_AFSEL7_Pos);
	
	SPI1->CR1 |= (SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_SSI | SPI_CR1_SSM);
	SPI1->CR1 |= SPI_CR1_SPE;
}

void SpiRead(uint8_t* data, uint32_t count)
{
	GPIOA->ODR &= ~GPIO_ODR_ODR_4;

	do
		{
			while(!(SPI1->SR & SPI_SR_TXE));

			(*(__IO uint8_t *)((uint32_t)SPI1 + 0x0C)) = *data;			// MODE = 1 -> записали и читаем нужную инфу

			while (SPI1->SR & SPI_SR_BSY);
			while(!(SPI1->SR & SPI_SR_RXNE));

			*data++ = (*(__IO uint8_t *)((uint32_t)SPI1 + 0x0C));
			
			count--;
		}while(count != 0);

	GPIOA->ODR |= GPIO_ODR_ODR_4;
}

void SpiWrite(uint8_t* data, uint32_t count)
{
	GPIOA->ODR &= ~GPIO_ODR_ODR_4;
	uint16_t r;

	do
		{
			while(!(SPI1->SR & SPI_SR_TXE));

			(*(__IO uint8_t *)((uint32_t)SPI1 + 0x0C)) = *data++;						// MODE = 0 -> записываем нужную инфу и читаем

			while (SPI1->SR & SPI_SR_BSY);

			while(!(SPI1->SR & SPI_SR_RXNE));
			
			r = (*(__IO uint8_t *)((uint32_t)SPI1 + 0x0C));

			count--;
		}while(count != 0);

	GPIOA->ODR |= GPIO_ODR_ODR_4;
}
