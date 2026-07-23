#include <stdint.h>
#include "gpio.h"
#include "usart1.h"
#include "timer1.h"
#include "i2c.h"
#include "spi.h"

void SystemInit(void){

}

int main(void){
    
    Led_Init();
    Usart1_Init();
    Timer1_Init();
    I2C_Init();
    Spi1_Init();
    while(1)
    {
        if (Button_Get_State() == 1)
        {
            LedCtrl(LED_BLUE, ON_LED);
            LedCtrl(LED_GREEN, ON_LED);
            LedCtrl(LED_ORANGE, ON_LED);
            LedCtrl(LED_RED, ON_LED);
        }
        else 
        {
            LedCtrl(LED_BLUE, OFF_LED);
            LedCtrl(LED_GREEN, OFF_LED);
            LedCtrl(LED_ORANGE, OFF_LED);
            LedCtrl(LED_RED, OFF_LED);
        }

    }

    return 0;
}
