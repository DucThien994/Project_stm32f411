#include "timer1.h"
#include "gpio.h"

void Timer1_Init(void)
{
    //enable clock for timer 1 
    volatile uint32_t* RCC_APB2ENR = (volatile uint32_t*)(RCC_BASE_ADDR + 0x44);
    RCC_APB2ENR |= 1 << 0;

    volatile uint16_t* TIM1_PSC     = (volatile uint16_t*)(TIM1_BASE_ADDR + 0x28);
    volatile uint16_t* TIM1_ARR     = (volatile uint16_t*)(TIM1_BASE_ADDR + 0x2C);
    volatile uint16_t* TIM1_CR1     = (volatile uint16_t*)(TIM1_BASE_ADDR + 0x00);
    volatile uint16_t* TIM1_DIER    = (volatile uint16_t*)(TIM1_BASE_ADDR + 0x0C);
    volatile uint32_t* ISER0        = (volatilie uint32_t*)(0xE000E100); // enable interrupt

    TIM1_PSC = 16 - 1; 
    TIM1_ARR = 1000;
    TIM1_DIER |= 1 << 0;
    ISER0 |= 1 << 25; 
    TIM1_CR1 |= 1 << 0; // count enable 
}

volatile int time_cnt = 0; 

void TIM1_UP_TIM10_IRQHandler()
{
    time_cnt++;
    volatile uint16_t* TIM1_SR = (volatile uint16_t*)(TIM1_BASE_ADDR + 0x10);
    TIM1_SR &= ~(1 << 0);

}