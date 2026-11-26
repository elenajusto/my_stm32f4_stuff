#include "spi.h"
#include "gpio.h"
#include "stm32f411xe.h"

void spi1_init(void){
    // Enable clock to GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    
    // Enable clock to peripheral
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // Configure CLK1 - PA5
    gpio_init(GPIOA, 5, GPIO_MODE_AF, GPIO_OTYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_AF5);

    // Configure MISO - PA6
    gpio_init(GPIOA, 6, GPIO_MODE_AF, GPIO_OTYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_AF5);

    // Configure MOSI - PA7
    gpio_init(GPIOA, 7, GPIO_MODE_AF, GPIO_OTYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_AF5);

    // Configure CS - PA4
    gpio_init(GPIOA, 4, GPIO_MODE_OUTPUT, GPIO_OTYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_AF0);
    gpio_write(GPIOA, 4, GPIO_HIGH);    // CS line high while idle

    // Configure CR1
    SPI1->CR1 &= ~SPI_CR1_SPE;      // Disable SPI during configuration
    SPI1->CR1 |= SPI_CR1_BR_2;      // Set baud rate 
    SPI1->CR1 |= SPI_CR1_BR_0;      // Set baud rate 
    SPI1->CR1 |= SPI_CR1_SSM;       // Set software slave management - Drive own CS pin
    SPI1->CR1 |= SPI_CR1_SSI;       // Set internal slave select - Drive own CS pin
    SPI1->CR1 |= SPI_CR1_MSTR;      // Set to master configuration

    // Enable SPI
    SPI1->CR1 |= SPI_CR1_SPE;
}