#ifndef USART1_H
#define USART1_H

#define USART1_BASE_ADDR 0x40011000

#define USART1_BRR  (*(volatile uint32_t*)(USART1_BASE_ADDR + 0x08))
#define USART1_CR1  (*(volatile uint32_t*)(USART1_BASE_ADDR + 0x0C))
#define USART1_CR2  (*(volatile uint32_t*)(USART1_BASE_ADDR + 0x10))
#define USART1_CR3  (*(volatile uint32_t*)(USART1_BASE_ADDR + 0x14))
#define USART1_SR   (*(volatile uint32_t*)(USART1_BASE_ADDR + 0x00))
#define USART1_DR   (*(volatile uint32_t*)(USART1_BASE_ADDR + 0x04))

void Usart1_Config(void);
void Usart1_Init(void);
void USART1_IRQHandler(void);
void USART_SendChar(char c);
void USART_SendString(char* str);

#endif
