#include "timer.h"

void Tim_Init(){
    RCC->APB2ENR = RCC_APB2ENR_TIM1EN; 
    TIM1->PSC = 16 - 1; 
    TIM1->ARR = 1000; 
    TIM1->DIER = TIM_DIER_UIE;
    TIM1->CR1 = TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}   