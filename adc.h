#include <stdint.h>

#define ADC1_BASE_ADDR        0x40012000
#define ADC_COMMON_BASE_ADDR  0x40012300

// kenh ADC1_IN18: noi voi cam bien nhiet do noi (internal temp sensor) / VBAT
#define ADC_TEMPSENSOR_CHANNEL 18

uint16_t ADC1_ReadRaw(void);
void ADC1_TempSensor_Init(void);
float ADC1_ReadTemperature(void);
