#include "gpio.h"

void pin_high(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1UL << pin);
}

void pin_low(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1UL << (pin + 16));
}

bool pin_read(GPIO_TypeDef *port, uint8_t pin) {
	return (port->IDR >> pin) & 1;
}
