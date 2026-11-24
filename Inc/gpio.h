#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f4xx.h"
#include <stdint.h>

// Read-modify-write: clear (mask << shift) in reg, then write value there
#define SET_BITS(reg, shift, mask, value) \
((reg) = ((reg) & ~((uint32_t)(mask) << (shift))) | \
((((uint32_t)(value)) & (mask)) << (shift)))

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

// AFR[0]/AFR[1]: 4 bits per pin
typedef enum {
    GPIO_AF0  = 0,   // SYS (MCO, SWD, RTC_REFIN)
    GPIO_AF1  = 1,   // TIM1, TIM2
    GPIO_AF2  = 2,   // TIM3, TIM4, TIM5
    GPIO_AF3  = 3,   // TIM9, TIM10, TIM11
    GPIO_AF4  = 4,   // I2C1, I2C2, I2C3
    GPIO_AF5  = 5,   // SPI1-5 / I2S
    GPIO_AF6  = 6,   // SPI2-5 / I2S
    GPIO_AF7  = 7,   // SPI3, USART1, USART2
    GPIO_AF8  = 8,   // USART6
    GPIO_AF9  = 9,   // I2C2, I2C3
    GPIO_AF10 = 10,  // OTG_FS
    GPIO_AF11 = 11,
    GPIO_AF12 = 12,  // SDIO
    GPIO_AF13 = 13,
    GPIO_AF14 = 14,
    GPIO_AF15 = 15   // EVENTOUT
} gpio_af_t;

// Configure one pin. Also enables the port's clock in RCC->AHB1ENR.
// af (0-15) is only applied when mode is GPIO_MODE_AF.
void gpio_init(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode,
               gpio_otype_t otype, gpio_speed_t speed, gpio_pull_t pull,
               gpio_af_t af);

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} gpio_state_t;

void gpio_write(GPIO_TypeDef *port, uint8_t pin, gpio_state_t value);

#endif /* GPIO_H_ */
