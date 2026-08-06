#include "dma.h"

void DMA_Init(void) {
    uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
    *RCC_AHB1ENR = 1 << 22; 
    
    uint32_t* DMA_S2M0AR = *(uint32_t*)(DMA2_BASE_ADDR + )
}

void DMA2_Stream0_IRQHandler(){

}