#define USART1_BASE_ADDR (*(volatile uint32_t*)(0x40011000))

void Usart1_Init(void);
void USART_SendChar(char c);
void USART_SendString(char* str);