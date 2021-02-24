#ifndef _SPI_
#define _SPI_

#include "stm32f4xx.h"

extern void SpiInit(void);
extern void SpiRead(uint8_t*, uint32_t);
extern void SpiWrite(uint8_t*, uint32_t);

#endif
