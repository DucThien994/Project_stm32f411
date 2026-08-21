#include "gpio.h"
#include "usart1.h"
#include <stdint.h>

void Usart1_Config(void)
{
    // enable clock
    RCC_APB2ENR |= 1 << 4;
    RCC_AHB1ENR |= 1 << 1; 

    // config function
    GPIOB_MODER &= ~(0b1111 << 12);
    GPIOB_MODER |= (0b1010 << 12); // set alternate function for PB6 and PB7
    GPIOB_AFRL &= ~(0xFF << 24);
    GPIOB_AFRL |= (0x77 << 24); // set alternate function for PB6 and PB7
}

void Usart1_Init(void)
{
    // enable clock 
    RCC_APB2ENR |= 1 << 4;

    // config 
    USART1_BRR = 0x683; // if baudrate = 11520 -> 0x8A

    USART1_CR1 |= 1 << 12; // word length
    USART1_CR1 &= ~(1 << 10); // check parity enable
    USART1_CR2 &= ~ (0b11 << 12); // stop bit
    USART1_CR1 |= 1 << 2; // enable receive
    USART1_CR1 |= 1 << 3; // enable transmit
    USART1_CR3 |= 1 << 7; //  DMAT = 1 | DMA transmit
    USART1_CR1 |= 1 << 5; // enable RXNE interrupt
    USART1_CR1 |= 1 << 13; //enable usart
    ISER1 |=  1 << 5;   // NVIC enable 

}

volatile char rx_char;
void USART1_IRQHandler(void)
{
    if (USART1_SR & (1 << 5)) // RXNE: có byte mới
    {
        rx_char = USART1_DR; // đọc dữ liệu từ thanh ghi dữ liệu        
        
        if (rx_char == '0') 
        {
            Led_on_off(0); // led off
            USART_SendString("LED OFF\n");
        }
        else if (rx_char == '1')
        {
            Led_on_off(1); // led on
            USART_SendString("LED ON\n");
        }
        else{
            USART_SendString("Invalid command\n");
        }

    }
}

void USART_SendChar(char c)
{
    while (!(USART1_SR & (1 << 7))); // wait TXE: thanh ghi truyen rong
    USART1_DR = c & 0xFF;
    while (!(USART1_SR & (1 << 6))); // wait TC: hoan tat truyen
}

void USART_SendString(char* str)
{
    while (*str){
        USART_SendChar(*str++);
    }
}
