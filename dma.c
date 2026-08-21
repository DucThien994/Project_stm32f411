#include "dma.h"
#include "usart1.h"

/*
  - Target: DMA send UART, temperature of stm32f4 chip
  - Stream 7 
  - Channel 
*/

static volatile uint8_t dma_tx_busy = 0;

void DMA2_USART1_TX_Init(void) {

  RCC_AHB1ENR |= 1 << 22;
  DMA2_S7CR &= ~ (1 << 0); // disable stream 7 before config register
  while (DMA2_S7CR & (1 << 0)); // wait until disable finish 

  // write 1 to clear | CLEAR flag stream 7 
  DMA2_HIFCR |= (1 << 22);
  DMA2_HIFCR |= (0xF << 24);

  // config S7CR 
  DMA2_S7CR |= (4 << 25); // channel 5 : 101 
  DMA2_S7CR |= 1 << 6;     // 01 -> memory-to-peripheral
  DMA2_S7CR |= 1 << 10;   // MINC : memory increment mode 
  DMA2_S7CR |= 1 << 4;    // tranfer complete interrupt enable   

  // data reg usart1
  DMA2_S7AR = (uint32_t)(USART1_BASE_ADDR + 0x04); 

  // enable NVIC
  ISER2 |= (1 << (70 - 64)); 

}

void DMA2_USART1_TX_Send(uint8_t *src_addr, uint16_t lenght) {

  while (DMA2_S7CR & (1 << 0)); // wait until disable finish 
  dma_tx_busy = 1;

  // tat stream 7 
  DMA2_S7CR &= ~(1 << 0);
  while (DMA2_S7CR & (1 << 0)); // wait until disable finish 

  // clear flag in HIFCR
  DMA2_HIFCR |= (1 << 22);
  DMA2_HIFCR |= (0xF << 24);

  // update addr RAM and length
  DMA2_S7M0AR = (uint32_t)(src_addr);
  DMA2_S7NDTR = length;

  // enable STREAM DMA to start
  DMA2_S7SR |= 1 << 0;

}

void DMA2_USART1_IsBusy(void){
  return dma_tx_busy; 
}

void DMA2_Stream7_IRQHandler (void){
  // check flag TCIF7 (transfer complete stream 7)
  if (DMA2_HISR & (1 << 27)){
    // CLEAR FLAG 
    DMA2_HIFCR |= 1 << 27;
    dma_tx_busy = 0; 
  }
}
