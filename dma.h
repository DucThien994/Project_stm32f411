#ifndef DMA_H
#define DMA_H

#include "gpio.h"
#include "stdint.h"

#define DMA1_BASE_ADDR  0x40026000
#define DMA2_BASE_ADDR  0x40026400

#define DMA2_HISR       (*(volatile uint32_t *)(DMA2_BASE_ADDR + 0x04))
#define DMA2_HIFCR      (*(volatile uint32_t *)(DMA2_BASE_ADDR + 0x0C))
#define DMA2_S7CR       (*(volatile uint32_t *)(DMA2_BASE_ADDR + 0x10 + 0x18 * 7))
#define DMA2_S7PAR      (*(volatile uint32_t *)(DMA2_BASE_ADDR + 0x18 + 0x18 * 7))
#define DMA2_S7M0AR     (*(volatile uint32_t *)(DMA2_BASE_ADDR + 0x1C + 0x18 * 7))
#define DMA2_S7NDTR     (*(volatile uint32_t *)(DMA2_BASE_ADDR + 0x14 + 0x18 * 7))


void DMA2_USART1_TX_Init(void);
void DMA2_USART1_TX_Send(uint8_t *src_addr, uint16_t length);
uint8_t DMA2_USART1_IsBusy(void);

#endif
