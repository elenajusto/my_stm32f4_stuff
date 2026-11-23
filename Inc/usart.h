#ifndef USART_H_
#define USART_H_

#include "stm32f4xx.h"
#include "gpio.h"

void usart2_init(void);
void usart2_transmit(char data);
uint8_t usart2_receive(void);

#endif /* USART */