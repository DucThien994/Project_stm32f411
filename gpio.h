#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

// define base address 
#define GPIOB_BASE_ADDR 0x40020400
#define GPIOA_BASE_ADDR 0x40020000
#define GPIOC_BASE_ADDR 0x40020800
#define GPIOD_BASE_ADDR 0x40020C00
#define GPIOE_BASE_ADDR 0x40021000
#define EXTI_BASE_ADDR  0x40013C00
#define RCC_BASE_ADDR  	0x40023800

// define bus clock register 
#define RCC_AHB1ENR (*(volatile uint32_t*)(RCC_BASE_ADDR + 0x30))
#define RCC_APB1ENR (*(volatile uint32_t*)(RCC_BASE_ADDR + 0x40))
#define RCC_APB2ENR (*(volatile uint32_t*)(RCC_BASE_ADDR + 0x44))

// define for gpio register
#define GPIOA_MODER 	(*(volatile uint32_t*)(GPIOA_BASE_ADDR))
#define GPIOB_MODER 	(*(volatile uint32_t*)(GPIOB_BASE_ADDR))
#define GPIOC_MODER 	(*(volatile uint32_t*)(GPIOC_BASE_ADDR))
#define GPIOD_MODER 	(*(volatile uint32_t*)(GPIOD_BASE_ADDR))
#define GPIOE_MODER 	(*(volatile uint32_t*)(GPIOD_BASE_ADDR))


#define GPIOA_IDR 		(*(volatile uint32_t*)(GPIOA_BASE_ADDR + 0x14))
#define GPIOA_AFRL 		(*(volatile uint32_t*)(GPIOA_BASE_ADDR + 0x20))

#define GPIOB_AFRL 		(*(volatile uint32_t*)(GPIOB_BASE_ADDR + 0x20))
#define GPIOB_AFRH 		(*(volatile uint32_t*)(GPIOB_BASE_ADDR + 0x24))
#define GPIOB_OTYPER 	(*(volatile uint32_t*)(GPIOB_BASE_ADDR + 0x20))

#define GPIOD_ODR		(*(volatile uint32_t*)(GPIOD_BASE_ADDR + 0x14))

#define GPIOE_ODR 		(*(volatile uint32_t*)(GPIOE_BASE_ADDR))

#define ISER0       	(*(volatile uint32_t*)(0xE000E100))
#define ISER1       	(*(volatile uint32_t*)(0xE000E104))
#define ISER2       	(*(volatile uint32_t*)(0xE000E108))

#pragma once 
typedef enum{
	// dat dung theo thu tu cua schematic
	LED_GREEN,
	LED_ORANGE,
	LED_RED,
	LED_BLUE,
}led_t;

typedef enum{
	OFF_LED,
	ON_LED,
}led_state_t;

void Led_Init();
void LedCtrl(led_t led, led_state_t state);
void Button_Init();
char Button_Get_State();
void Led_on_off(uint8_t state);

#endif
