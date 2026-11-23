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

void usart2_transmit(char data) {
    // TXE - Transmit data register empty flag - wait until USART2->DR is empty before writing new value
    while ((USART2->SR & USART_SR_TXE) == 0) {
    };
    USART2->DR = data;
}

void usart2_print(char *str){
    // Loop through string until null terminator reached
    while(*str != '\0') {
        // Send characters within the string
        usart2_transmit(*str);  // Pass pointer to character in string
        str++;                       // Increment pointer reference to next character
    }
}

uint8_t usart2_receive(void) {
    // RXNE - Read data register not empty flag - wait until data has been received before reading
    while ((USART2->SR & USART_SR_RXNE) == 0) {
    };
    return USART2->DR & 0xFF;            // 0xFF keeps lowest 8 bits
}