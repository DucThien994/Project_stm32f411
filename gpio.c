#include "gpio.h"
#include <stdint.h>

int GPIO_Init(void)
{
    /* GPIO Ports Clock Enable */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 

    /* PB6 and PB7 for USART1*/
    // Clear bits for PB6 PB7 to reset mode 
    GPIOB->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7); 
    // Set bits for PB6 PB7 to alternate function mode 
    GPIOB->MODER |= (GPIO_MODER_MODER6 | GPIO_MODER_MODER7); 

    // Set PB6 PB7 to alternate function mode
    GPIOB->AFR[0] &= ~(0xF << (6 * 4) | 0xFU << (7 * 4));
    GPIOB->AFR[0] |= (0xF << (6 * 4) | 0xF << (7 * 4));
    
    return 0;
}

void Led_Init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable clock for GPIOD

    // clear bits for pd12 -> pd15 
    GPIOD->MODER &= ~(0xFF << 24);

    // set output mode for pd12 -> pd15
    GPIOD->MODER |= (0x55 << 24);
}

void Led_control(led_t led, led_state_t state){
    if (state == LED_ON){
        GPIOD->ODR |= (1 << (led + 12)); 
    }
    else{
        GPIOD->ODR &= ~(1 << (led + 12)); 
    }
}