#include "i2c.h"
#include <stdint.h>
#include "gpio.h"

/*
    I2C1 for LSM303AGR
    PB6 and PB9 config open drain 
*/ 

void I2C_Init(void){

    // enable clock 
    uint32_t* RCC_APB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x40);
    uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
    
    *RCC_APB1ENR |= 1 << 22; 
    *RCC_AHB1ENR |= 1 << 1;

    // config function 
    uint32_t* GPIOB_MODER   = (uint32_t*)(GPIOB_BASE_ADDR +0x00);
    uint32_t* GPIOB_OTYPER  = (uint32_t*)(GPIOB_BASE_ADDR +0x04);
    uint32_t* GPIOB_AFRL    = (uint32_t*)(GPIOB_BASE_ADDR +0x20);
    uint32_t* GPIOB_AFRH    = (uint32_t*)(GPIOB_BASE_ADDR +0x24);

    uint32_t* I2C1_CR1    = (uint32_t*)(I2C1_BASE_ADDR + 0x00);
    uint32_t* I2C1_CR2    = (uint32_t*)(I2C1_BASE_ADDR + 0x04);
    uint32_t* I2C1_DR     = (uint32_t*)(I2C1_BASE_ADDR + 0x10);
    uint32_t* I2C1_SR1    = (uint32_t*)(I2C1_BASE_ADDR + 0x14);
    uint32_t* I2C1_SR2    = (uint32_t*)(I2C1_BASE_ADDR + 0x18);
    uint32_t* I2C1_CCR    = (uint32_t*)(I2C1_BASE_ADDR + 0x1C);


    *GPIOB_MODER &= ~(0b11 << 12);
    *GPIOB_MODER &= ~(0b11 << 18);
    *GPIOB_MODER |= (0b10 << 12);
    *GPIOB_MODER |= (0b10 << 18);
    *GPIOB_AFRL &= ~(0xF << 24);
    *GPIOB_AFRL |= (0b0100 << 24);
    *GPIOB_AFRH &= ~(0xF << 4);
    *GPIOB_AFRH |= (0b0100 << 4);

    *I2C1_CR2 &= ~(0b11111 << 0);
    *I2C1_CR2 |= (16 << 0);
    *I2C1_CCR &= ~(0xFFF << 0);
    *I2C1_CCR |= (80 << 0); // 100MHz
    *I2C1_CR1 |= (1 << 0); // enable peripheral 
}

void I2C_WriteData(void)
{
    uint32_t* I2C1_CR1    = (uint32_t*)(I2C1_BASE_ADDR + 0x00);
    uint32_t* I2C1_SR1    = (uint32_t*)(I2C1_BASE_ADDR + 0x14);


    //This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
    *I2C1_CR1 |= 1 << 8; // start bit on bus wires 
    *I2C1_SR1 |= 1 << 0; // start bit master mode


}

void I2C_ReadData(void)
{


}