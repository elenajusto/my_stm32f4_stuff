#include "gpio.h"

static void gpio_enable_clock(GPIO_TypeDef *port) {
	if (port == GPIOA) {
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	} else if (port == GPIOB) {
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	} else if (port == GPIOC) {
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	} else if (port == GPIOD) {
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	} else if (port == GPIOE) {
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	} else if (port == GPIOH) {
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
	}

	(void)RCC->AHB1ENR;   // dummy read: wait for the clock to start (errata)
}

void gpio_init(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode,
               gpio_otype_t otype, gpio_speed_t speed, gpio_pull_t pull,
               uint8_t af) {

	// Clock
	gpio_enable_clock(port);

	// MODER
	SET_BITS(port->MODER, pin * 2, 0x3, mode);

	// OTYPER
	SET_BITS(port->OTYPER, pin, 0x1, otype);

	// OSPEEDR
	SET_BITS(port->OSPEEDR, pin * 2, 0x3, speed);

	// PUPDR
	SET_BITS(port->PUPDR, pin * 2, 0x3, pull);

	// AF: AFR[0] holds pins 0-7, AFR[1] holds pins 8-15, 4 bits per pin
	if (mode == GPIO_MODE_AF) {
		SET_BITS(port->AFR[pin >> 3], (pin & 0x7) * 4, 0xF, af);
	}
}

void pin_high(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1UL << pin);
}

void pin_low(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1UL << (pin + 16));
}
