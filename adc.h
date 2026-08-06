#include <stdint.h>

#define ADC1_BASE_ADDR        0x40012000
#define ADC_COMMON_BASE_ADDR  0x40012300

// kenh ADC1_IN18: noi voi cam bien nhiet do noi (internal temp sensor) / VBAT
#define ADC_TEMPSENSOR_CHANNEL 18

#define ADC1_CR2    (*(volatile uint32_t*)(ADC1_BASE_ADDR + 0x08))
#define ADC1_SMPR1  (*(volatile uint32_t*)(ADC1_BASE_ADDR + 0x0C))
#define ADC1_SQR1   (*(volatile uint32_t*)(ADC1_BASE_ADDR + 0x2C))
#define ADC1_SQR3   (*(volatile uint32_t*)(ADC1_BASE_ADDR + 0x34))
#define ADC1_SR     (*(volatile uint32_t*)(ADC1_BASE_ADDR + 0x00))
#define ADC1_DR     (*(volatile uint32_t*)(ADC1_BASE_ADDR + 0x4C))

#define ADC_CCR     (*(volatile uint32_t*)(ADC_COMMON_BASE_ADDR + 0x04))


uint16_t ADC1_ReadRaw(void);
void ADC1_TempSensor_Init(void);
float ADC1_ReadTemperature(void);
