#include "dma.h"

void DMA2_USART1_TX_Init(){

    // enable clock 
    RCC_AHB1ENR |= 1 << 22;

}

void DMA2_USART1_TX_Send(){
    
}