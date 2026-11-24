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

	// Init PA4 for external LED
	gpio_init(GPIOA, 4, GPIO_MODE_OUTPUT, GPIO_OTYPE_PUSH_PULL, GPIO_SPEED_FAST, GPIO_PULL_NONE, GPIO_AF0);

	/* Main Program Loop */
	while(1) {
		// Transmit
		usart2_print("Meow\r\n");
		gpio_write(GPIOA, 4, GPIO_HIGH);
		delay(500);

		if ((USART2->SR & USART_SR_RXNE) != 0) {
			char received_char = usart2_receive();
			usart2_print("Received: ");
			usart2_transmit(received_char);
			usart2_print("\r\n");

			if (received_char == 'd' || received_char == 'D') {
				usart2_print("DEEZ NUTS\r\n");
			}

			gpio_write(GPIOA, 4, GPIO_LOW);
			delay(500);
		}
	}
}