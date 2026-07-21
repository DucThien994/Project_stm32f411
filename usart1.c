#include "gpio.h"
#include "usart1.h"
#include <stdint.h>

void Usart1_Init(void)
{
    uint32_t* RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0x44);
    *RCC_APB2ENR |= 1 << 4;

    uint32_t* USART1_BRR = (uint32_t*)(USART1_BASE_ADDR + 0x08);
    uint32_t* USART1_SR = (uint32_t*)(USART1_BASE_ADDR + 0x00);
    uint32_t* USART1_CR1 = (uint32_t*)(USART1_BASE_ADDR + 0x0C);
    uint32_t* USART1_CR2 = (uint32_t*)(USART1_BASE_ADDR + 0x10);

    *USART1_BRR = 0x683;
    *USART1_CR1 |= 1 << 12; // word length
    *USART1_CR1 |= 1 << 9; // odd parity
    *USART1_CR1 |= 1 << 10; // check parity enable
    *USART1_CR2 &= ~ (0b11 << 12); // stop bit
    *USART1_CR1 |= 1 << 2; // enable receive
    *USART1_CR1 |= 1 << 3; // enable transmit
    *USART1_CR1 |= 1 << 5; // enable RXNE interrupt
    *USART1_CR1 |= 1 << 13; //enable usart

}

void USART_SendChar(char c)
{
    uint32_t* USART1_SR = (uint32_t*)(USART1_BASE_ADDR + 0x00);
    uint32_t* USART1_DR = (uint32_t*)(USART1_BASE_ADDR + 0x04);

    while (!(*USART1_SR & (1 << 7))); // wait TXE: thanh ghi truyen rong
    *USART1_DR = c & 0xFF;
    while (!(*USART1_SR & (1 << 6))); // wait TC: hoan tat truyen
}

void USART_SendString(char* str)
{
    while (*str){
        USART_SendChar(*str++);
    }
}
