#include <stdint.h>
#include "gpio.h"
#include "usart1.h"
#include "timer1.h"
#include "i2c.h"

void SystemInit(void){

}

int main(void){
    
    Led_Init();
    Usart1_Init();
    Timer1_Init();
    I2C_Init();
    LedCtrl(LED_GREEN, ON_LED);
    LedCtrl(LED_BLUE, ON_LED);
    LedCtrl(LED_RED, ON_LED);
    LedCtrl(LED_ORANGE, ON_LED);
    while(1)
    {

    }

    return 0;
}
