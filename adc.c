#include "adc.h"
#include "gpio.h"

// Cau hinh ADC1 kenh 18 (internal temperature sensor), single conversion,
// software trigger. Tham khao RM0383: TSVREFE (ADC_CCR bit 23) phai bat de wake
// up cam bien nhiet + VREFINT.
void ADC1_TempSensor_Init(void) {
  // enable clock ADC1 (APB2)
  RCC_APB2ENR |= 1 << 8;

  // sample time kenh 18 = 480 chu ky (max), datasheet yeu cau toi thieu ~10us
  // cho temp sensor
  ADC1_SMPR1 &= ~(0b111 << 24);
  ADC1_SMPR1 |= (0b111 << 24);

  // regular sequence: L = 0 -> 1 conversion, SQ1 = channel 18
  ADC1_SQR1 &= ~(0b1111 << 20);
  ADC1_SQR3 &= ~(0b11111 << 0);
  ADC1_SQR3 |= (ADC_TEMPSENSOR_CHANNEL << 0);

  // bat temp sensor + VREFINT
  ADC_CCR |= (1 << 23); // TSVREFE

  // bat ADC1
  ADC1_CR2 |= (1 << 0); // ADON
}

// Trigger 1 lan chuyen doi (software start), doi EOC, tra ve gia tri raw 12-bit
uint16_t ADC1_ReadRaw(void) {
  ADC1_CR2 |= (1 << 30); // SWSTART
  while (!(ADC1_SR & (1 << 1)))
    ; // wait EOC
  uint16_t data = (uint16_t)(ADC1_DR & 0xFFFF);
  ADC1_SR &= ~(1 << 1); // clear EOC

  return data;
}

float ADC1_ReadTemperature(void) {
  uint16_t raw = ADC1_ReadRaw();
  float vsense = (raw * 3.3f) / 4095.0f;
  float temperature = ((vsense - 0.76f) / 0.0025f) + 25.0f;

  return temperature;
}
