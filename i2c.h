#include <stdint.h>

#define I2C1_BASE_ADDR 0x40005400
#define I2C2_BASE_ADDR 0x40005800
#define I2C3_BASE_ADDR 0x40005C00

void I2C_Init(void);
void I2C_WriteData(uint8_t slave_reg_addr, uint8_t slave_reg_val);
uint8_t I2C_ReadData(uint8_t slave_reg_addr);