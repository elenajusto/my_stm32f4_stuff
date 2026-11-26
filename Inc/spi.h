#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>

void spi1_init(void);
void spi1_transmit_8bit(uint8_t data);

#endif /* SPI_H_ */
