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

    }

    return 0;
}
