#include "stm32f411xe.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
#include "spi.h"
#include <stdint.h>

/* Main Program Entry */
int main(void) {
	// Init peripheral 
	spi1_init();

	/* Main Program Loop */
	while(1) {
		// Set CS line to low - start SPI transmission
		gpio_write(GPIOA, 3, GPIO_LOW);

		// Transmit
		spi1_transmit_8bit(0x5A);

		// Check if peripheral busy before continuing
		while(SPI1->SR & SPI_SR_BSY){
		};

		// Set CS line to high - end SPI transmission
		gpio_write(GPIOA, 3, GPIO_HIGH);
	}
}