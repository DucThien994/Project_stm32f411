#include <stm32f4xx.h>
#include <stm32f411xe.h>
#include <system_stm32f4xx.h>

typedef enum{
    LED_GREEN = 0,
    LED_ORANGE,
    LED_RED,
    LED_BLUE
}led_t;

typedef enum{
    LED_OFF,
    LED_ON
}led_state_t;

void Led_Init(void);
void Led_control(led_t led, led_state_t state);
