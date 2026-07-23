#define USART1_BASE_ADDR 0x40011000

void Usart1_Config(void);
void Usart1_Init(void);
void USART1_IRQHandler(void);
void USART_SendChar(char c);
void USART_SendString(char* str);