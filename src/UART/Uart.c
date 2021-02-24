#include "Uart.h"

void Uart2Init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	GPIOA->MODER  |=  (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1);
	GPIOA->MODER  &= ~(GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0);
	GPIOA->AFR[0] |= (0x07 << GPIO_AFRL_AFSEL2_Pos) | (0x07 << GPIO_AFRL_AFSEL3_Pos);
   
  USART2->BRR  = 0x16C;	//0x5B1

	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE);
//	NVIC_EnableIRQ(USART1_IRQn);
}


void Send(char* Array)
{
	while(*Array)
		{
			while(!(USART2->SR & USART_SR_TC));
			USART2->DR = *Array;
			Array++;
	}
}
