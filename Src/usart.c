#include "usart.h"
#include "gpio.h"
#include "stm32f411xe.h"
#include "stm32f4xx.h"
#include <stdint.h>

#define SYSTEM_CLOCK    (16UL * 1000UL * 1000UL)   // 16 MHz
#define USART_BAUD      9600UL

// Use PA2 (TX2) and PA3 (RX2) for USART
void usart2_init(void) {
    // Enable clock to USART2 peripheral
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	

    // Enable clock to PORTA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set PA2 for TX2 - AF7 
    MODIFY_FIELD(GPIOA->MODER, GPIO_MODER_MODE2, GPIO_MODE_AF);  
    MODIFY_FIELD(GPIOA->AFR[0], GPIO_AFRL_AFSEL2, 7);           

    // Set PA3 for RX2 - AF7
    MODIFY_FIELD(GPIOA->MODER, GPIO_MODER_MODE3, GPIO_MODE_AF);  
    MODIFY_FIELD(GPIOA->AFR[0], GPIO_AFRL_AFSEL3, 7); 

    // Set baud rate - 9600
    USART2->BRR = SYSTEM_CLOCK / USART_BAUD;   // f_ck / baud 

    // Enable transmitter
    USART2->CR1 |= USART_CR1_TE;

    // Enable receiver
    USART2->CR1 |= USART_CR1_RE;

    // Enable UART
    USART2->CR1 |= USART_CR1_UE;
}

void usart2_transmit(uint8_t data) {
    while ((USART2->SR & USART_SR_TXE) == 0) {
    };
    USART2->DR = data;
}

uint8_t usart2_receive(void) {
    while ((USART2->SR & USART_SR_RXNE) == 0) {
    };
    return USART2->DR & 0xFF;            // 0xFF keeps low 8 bits
}