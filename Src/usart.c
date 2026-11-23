#include "usart.h"
#include "gpio.h"
#include "stm32f411xe.h"
#include "stm32f4xx.h"
#include <stdint.h>

#define USART_CLOCK_HZ  (16UL * 1000UL * 1000UL)   // HSI 16 MHz, APB1 prescaler = 1
#define USART_BAUD      9600UL

// Use PA2 (TX2) and PA3 (RX2) for USART
void usart2_init(void) {
    // Enable clock to USART2 peripheral
    MODIFY_FIELD(RCC->APB1ENR, RCC_APB1ENR_USART2EN, 1);	

    // Enable clock to PORTA
    MODIFY_FIELD(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN, 1);

    // Set PA2 for TX2 - AF7
    MODIFY_FIELD(GPIOA->MODER, GPIO_MODER_MODE2, GPIO_MODE_AF);  
    MODIFY_FIELD(GPIOA->AFR[0], GPIO_AFRL_AFSEL2, 7);           

    // Set PA3 for RX2 - AF7
    MODIFY_FIELD(GPIOA->MODER, GPIO_MODER_MODE3, GPIO_MODE_AF);  
    MODIFY_FIELD(GPIOA->AFR[0], GPIO_AFRL_AFSEL3, 7); 

    // Set baud rate - 9600
    USART2->BRR = (USART_CLOCK_HZ + USART_BAUD / 2) / USART_BAUD;

    // Set parity - None
    MODIFY_FIELD(USART2->CR1, USART_CR1_PCE, 0);

    // Set data length - 8
    MODIFY_FIELD(USART2->CR1, USART_CR1_M, 0);
    
    // Set stop bit - 1
    MODIFY_FIELD(USART2->CR2, USART_CR2_STOP, 0);

    // Enable transmitter
    MODIFY_FIELD(USART2->CR1, USART_CR1_TE, 1);

    // Enable receiever
    MODIFY_FIELD(USART2->CR1, USART_CR1_RE, 1);

    // Enable UART
    MODIFY_FIELD(USART2->CR1, USART_CR1_UE, 1);
}

void usart2_transmit(uint8_t data) {
    while ((USART2->SR & USART_SR_TXE) == 0) {
    };
    USART2->DR = data;
}

uint8_t usart2_receive(void) {
    while ((USART2->SR & USART_SR_RXNE) == 0) {
    };
    return USART2->DR & 0xFF;            // 0xFF checks for 8 bits
}