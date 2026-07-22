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

void I2C_WriteData(uint8_t slave_reg_addr, uint8_t slave_reg_val)
{
    uint32_t* I2C1_CR1    = (uint32_t*)(I2C1_BASE_ADDR + 0x00);
    uint32_t* I2C1_SR1    = (uint32_t*)(I2C1_BASE_ADDR + 0x14);
    uint32_t* I2C1_DR     = (uint32_t*)(I2C1_BASE_ADDR + 0x10);
    uint32_t* I2C1_SR2    = (uint32_t*)(I2C1_BASE_ADDR + 0x18);

    //This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
    *I2C1_CR1 |= 1 << 8; // start bit on bus wires 
    // wait SB bit in SR1
    while (((*I2C1_SR1 >> 0) & 1) == 0); // wait for SB bit to be set
    // Send 7 slave add + 1 bit write (0b0011001 << 1 | 0)
    *I2C1_DR = 0b00110010; 
    while (((*I2C1_SR1 >> 1) & 1) == 0); 
    uint32_t temp = *I2C1_SR2; 

    // CHEKC ACK 
    while (((*I2C1_SR1 >> 10) & 1) == 1);

    // send command frame 0x1F 
    *I2C1_DR = slave_reg_addr;

    // check ack 
    while (((*I2C1_SR1 >> 10) & 1) == 1);


    // send write data 0b11000000
    *I2C1_DR = 0b11000000;
    while (((*I2C1_SR1 >> 2) & 1) == 0);

    // generate stop bit
    *I2C1_CR1 |= 1 << 9;
}

void I2C_ReadData(uint8_t slave_reg_addr)
{
    uint32_t* I2C1_CR1 = (uint32_t*)(I2C1_BASE_ADDR + 0x00);
    *I2C1_CR1 |= 1 << 8;
    uint32_t* I2C1_SR1 = (uint32_t*)(I2C1_BASE_ADDR + 0x14);
    while (((*I2C1_SR1 >> 0) & 1) == 0);
    // Send 7 slave add + 1 bit write
    uint32_t* I2C1_DR = (uint32_t*)(I2C1_BASE_ADDR + 0x10);
    *I2C1_DR = 0b00110010;
    while (((*I2C1_SR1 >> 1) &  1) == 0);
    uint32_t* I2C1_SR2 = (uint32_t*)(I2C1_BASE_ADDR + 0x18);
    uint32_t* temp = *I2C1_SR2;

    // check ack 
    while (((**I2C1_SR1 >> 10) & 1) == 1);

    //  send command frame
    *I2C1_DR = slave_reg_addr;
    while (((*I2C1_SR1 >> 2) & 1) == 0);

    // check ack
    while (((*I2C1_SR1 >> 10) & 1) == 1);

    // start bit 
    *I2C1_CR1 |= 1 << 8;
    while (((*I2C1_SR1 >> 0) & 1) == 0);

    // send 7 slave add + 1 bit read
    *I2C1_DR = 0b00110011;
    while (((*I2C1_SR1 >> 1) & 1) == 0);
    temp = *I2C1_SR2;

    // check ack
    while (((*I2C1_SR1 >> 10) & 1) == 1);

    // read data from slave
    while (((*I2C1_SR1 >> 6) & 1) == 0);
    uint8_t data = *I2C1_DR;

    // stop bit 
    *I2C1_CR1 |= 1 << 9;
    return data;


}