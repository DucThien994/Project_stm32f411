#include "gpio.h"
#include "stdint.h"

#define DMA1_BASE_ADDR (*(volatile uint32_t*)(0x40026000))
#define DMA2_BASE_ADDR (*(volatile uint32_t*)(0x40026400))
#define DMA2_BASE_ADDR (*(volatile uint32_t*)(0x40026400))

#define DMA2_HISR      (*(volatile uint32_t*)(0x40026400))
#define DMA2_HIFCR     (*(volatile uint32_t*)(0x40026400))
#define DMA2_S7CR      (*(volatile uint32_t*)(0x40026400 + 0x10 + 0X18 * 7))
#define DMA2_S7PAR     (*(volatile uint32_t*)(0x40026400 + 0x10 + 0X18 * 7))
#define DMA2_S7M0AR    (*(volatile uint32_t*)(0x40026400 + 0x10 + 0X18 * 7))

void DMA2_USART1_TX_Init(void);
void DMA2_USART1_TX_Send(uint8_t *src_addr, uint16_t lenght);
