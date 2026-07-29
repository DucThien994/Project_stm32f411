#include "gpio.h"
#include "adc.h"

// Cau hinh ADC1 kenh 18 (internal temperature sensor), single conversion, software trigger.
// Tham khao RM0383: TSVREFE (ADC_CCR bit 23) phai bat de wake up cam bien nhiet + VREFINT.
void ADC1_TempSensor_Init(void)
{
    // enable clock ADC1 (APB2)
    uint32_t* RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0x44);
    *RCC_APB2ENR |= 1 << 8;

    uint32_t* ADC1_CR2   = (uint32_t*)(ADC1_BASE_ADDR + 0x08);
    uint32_t* ADC1_SMPR1 = (uint32_t*)(ADC1_BASE_ADDR + 0x0C);
    uint32_t* ADC1_SQR1  = (uint32_t*)(ADC1_BASE_ADDR + 0x2C);
    uint32_t* ADC1_SQR3  = (uint32_t*)(ADC1_BASE_ADDR + 0x34);
    uint32_t* ADC_CCR    = (uint32_t*)(ADC_COMMON_BASE_ADDR + 0x04);

    // sample time kenh 18 = 480 chu ky (max), datasheet yeu cau toi thieu ~10us cho temp sensor
    *ADC1_SMPR1 &= ~(0b111 << 24);
    *ADC1_SMPR1 |= (0b111 << 24);

    // regular sequence: L = 0 -> 1 conversion, SQ1 = channel 18
    *ADC1_SQR1 &= ~(0b1111 << 20);
    *ADC1_SQR3 &= ~(0b11111 << 0);
    *ADC1_SQR3 |= (ADC_TEMPSENSOR_CHANNEL << 0);

    // bat temp sensor + VREFINT
    *ADC_CCR |= (1 << 23); // TSVREFE

    // bat ADC1
    *ADC1_CR2 |= (1 << 0); // ADON
}

// Trigger 1 lan chuyen doi (software start), doi EOC, tra ve gia tri raw 12-bit
uint16_t ADC1_ReadRaw(void)
{
    uint32_t* ADC1_CR2 = (uint32_t*)(ADC1_BASE_ADDR + 0x08);
    uint32_t* ADC1_SR  = (uint32_t*)(ADC1_BASE_ADDR + 0x00);
    uint32_t* ADC1_DR  = (uint32_t*)(ADC1_BASE_ADDR + 0x4C);

    *ADC1_CR2 |= (1 << 30); // SWSTART
    while (!(*ADC1_SR & (1 << 1))); // wait EOC
    uint16_t data = (uint16_t)(*ADC1_DR & 0xFFFF);
    *ADC1_SR &= ~(1 << 1); // clear EOC

    return data;
}

float ADC1_ReadTemperature(void)
{
    uint16_t raw = ADC1_ReadRaw();
    float vsense = (raw * 3.3f) / 4095.0f;
    float temperature = ((vsense - 0.76f) / 0.0025f) + 25.0f;

    return temperature;
}
