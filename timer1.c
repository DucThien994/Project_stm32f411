#include "timer1.h"
#include "gpio.h"
#include <stdint.h>

void Timer1_Init(void)
{
    //enable clock for timer 1
    RCC_APB2ENR |= 1 << 0;

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
    TIM1_SR &= ~(1 << 0);
}