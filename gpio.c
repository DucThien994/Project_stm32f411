#include "gpio.h"
#include <stdio.h>

void Led_Init(void)
{
    // CLOCK 
    volatile uint32_t* RCC_AHB1ENR = (volatile uint32_t*)(RCC_BASE_ADDR + 0x30);
    RCC_AHB1ENR |= 1 << 3;

    volatile uint32_t* GPIOD_MODER = (volatile uint32_t*)(GPIOD_BASE_ADDR + 0x00);
    // reset PD12 TO PD15 
    GPIOD_MODER &= (0xFF << 24);

    // set output pd12 to pd15 
    GPIOD_MODER |= (0x55 << 24);

    // ===== config usart1 =====
    volatile uint32_t* RCC_APB2ENR = (volatile uint32_t*)(RCC_BASE_ADDR + 0x44);
    RCC_APB2ENR |= 1 << 4;

    // PB6 PB7 TX RX
    volatile uint32_t* GPIOB_MODER = (volatile uint32_t*)(GPIOB_BASE_ADDR + 0x00);
    GPIOB_MODER &= ~(0xF << 12);
    GPIOB_MODER |= (0xA << 12); // set alternate function 0b1010

    volatile uint32_t* GPIOB_AFRL = (volatile uint32_t*)(GPIOB_BASE_ADDR + 0x20);
    GPIOB_AFRL |= ((0x7 << 24) | (0x7 << 28));
    // ===== end config usart1 =====
}


// control button 
void LedCtrl(led_t led, led_state_t state)
{

    volatile uint32_t* GPIOD_ODR = (volatile uint32_t*)(GPIOD_BASE_ADDR + 0x14);
    if (state == ON_LED)
    {
        GPIOD_ODR |= (1 << (led + 12));
    }
    else 
    {
        GPIOD_ODR &= ~(1 << (led + 12));
    }
}

// set PA0 -> button 
void Button_Init(void)
{
 	volatile uint32_t* RCC_AHB1ENR = (volatile uint32_t*)(RCC_BASE_ADDR + 0x30);
	RCC_AHB1ENR |= (1 << 0);

	volatile uint32_t* GPIOA_MODER = (volatile uint32_t*)(GPIOA_BASE_ADDR + 0x00);

	// set nut nhan PA0 la input 00
	GPIOA_MODER &= ~(0b11 << 0);   
}

char Button_Get_State()
{
    volatile uint32_t* GPIOA_IDR = (volatile uint32_t*)(GPIOA_BASE_ADDR + 0x10);
    if (((GPIOA_IDR >> 0) & 0x01) == 0x01) return 1;
    else return 0;
}