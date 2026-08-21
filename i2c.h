#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C1_BASE_ADDR 0x40005400
#define I2C2_BASE_ADDR 0x40005800
#define I2C3_BASE_ADDR 0x40005C00

#define I2C1_CR1    (*(volatile uint32_t*)(I2C1_BASE_ADDR + 0x00))
#define I2C1_CR2    (*(volatile uint32_t*)(I2C1_BASE_ADDR + 0x04))
#define I2C1_DR     (*(volatile uint32_t*)(I2C1_BASE_ADDR + 0x10))
#define I2C1_SR1    (*(volatile uint32_t*)(I2C1_BASE_ADDR + 0x14))
#define I2C1_SR2    (*(volatile uint32_t*)(I2C1_BASE_ADDR + 0x18))
#define I2C1_CCR    (*(volatile uint32_t*)(I2C1_BASE_ADDR + 0x1C))

void I2C_Init(void);
void I2C_WriteData(uint8_t slave_reg_addr, uint8_t slave_reg_val);
uint8_t I2C_ReadData(uint8_t slave_reg_addr);

#endif
