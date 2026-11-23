#include "stm32f411xe.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
#include <stdint.h>

/* Main Program Entry */
int main(void) {
	// Init peripheral 
	usart2_init();

	/* Main Program Loop */
	while(1) {
		// Transmit
		usart2_transmit('M');
		delay(500);
	}
}