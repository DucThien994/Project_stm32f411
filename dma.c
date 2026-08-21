#include "dma.h"
/*
    Target: DMA send UART, temperature of stm32f4 chip
*/

void DMA2_USART1_TX_Init(void) {

  // enable clock
  RCC_AHB1ENR |= 1 << 22;
}

void DMA2_USART1_TX_Send(uint8_t *src_addr, uint16_t lenght) {}
