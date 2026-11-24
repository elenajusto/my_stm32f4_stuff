#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f4xx.h"
#include <stdint.h>

// MODER: 2 bits per pin
typedef enum {
    GPIO_MODE_INPUT  = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_AF     = 2,
    GPIO_MODE_ANALOG = 3
} gpio_mode_t;

// OTYPER: 1 bit per pin
typedef enum {
    GPIO_OTYPE_PUSH_PULL  = 0,
    GPIO_OTYPE_OPEN_DRAIN = 1
} gpio_otype_t;

// OSPEEDR: 2 bits per pin
typedef enum {
    GPIO_SPEED_LOW       = 0,
    GPIO_SPEED_MEDIUM    = 1,
    GPIO_SPEED_FAST      = 2,
    GPIO_SPEED_VERY_FAST = 3
} gpio_speed_t;

// PUPDR: 2 bits per pin (3 is reserved)
typedef enum {
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP   = 1,
    GPIO_PULL_DOWN = 2
} gpio_pull_t;

// Read-modify-write: clear (mask << shift) in reg, then write value there
#define SET_BITS(reg, shift, mask, value) \
((reg) = ((reg) & ~((uint32_t)(mask) << (shift))) | \
((((uint32_t)(value)) & (mask)) << (shift)))

// Configure one pin. Also enables the port's clock in RCC->AHB1ENR.
// af (0-15) is only applied when mode is GPIO_MODE_AF.
void gpio_init(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode,
               gpio_otype_t otype, gpio_speed_t speed, gpio_pull_t pull,
               uint8_t af);

void pin_high(GPIO_TypeDef *port, uint8_t pin);
void pin_low(GPIO_TypeDef *port, uint8_t pin);

#endif /* GPIO_H_ */
