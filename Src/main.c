#include "stm32f4xx.h"
#include "gpio.h"
#include "delay.h"

/* Defines */
#define EXTERNAL_LED_PIN		1
#define EXTERNAL_LED_DELAY		1000

/* Prototypes */
void init_port_a(void);

/* Main Program Entry */
int main(void) {
	/* Init gpio ports */
	init_port_a();

	/* Main Program Loop */
	while(1) {
		pin_high(GPIOA, EXTERNAL_LED_PIN);
		delay(EXTERNAL_LED_DELAY);
		pin_low(GPIOA, EXTERNAL_LED_PIN);
		delay(EXTERNAL_LED_DELAY);
	}
}

/* Function definitions */
void init_port_a(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	init_pin(GPIOA, EXTERNAL_LED_PIN, GPIO_MODE_OUTPUT);    
}

