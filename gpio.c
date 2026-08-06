#include "gpio.h"
#include <stdio.h>
#include <stdint.h>

void Led_Init(void)
{
    // CLOCK
    RCC_AHB1ENR |= 1 << 3;
    // reset PD12 TO PD15
    GPIOD_MODER &= ~(0xFF << 24);
    // set output pd12 to pd15
    GPIOD_MODER |= (0x55 << 24);
}

// control button
void LedCtrl(led_t led, led_state_t state)
{

    uint32_t* GPIOD_ODR = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
    if (state == ON_LED)
    {
        *GPIOD_ODR |= (1 << (led + 12));
    }
    else
    {
        *GPIOD_ODR &= ~(1 << (led + 12));
    }
}

// set PA0 -> button
void Button_Init(void)
{
	RCC_AHB1ENR |= (1 << 0);
	GPIOA_MODER &= ~(0b11 << 0);
}

char Button_Get_State()
{
    if (((GPIOA_IDR >> 0) & 0x01) == 0x01) return 1;
    else return 0;
}