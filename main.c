#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "usart1.h"
#include "timer1.h"
//#include "i2c.h"
#include "spi.h"
#include "adc.h"
#include "dma.h"

void SystemInit(void){

}

int acb;
int global_1 = 0;
int global_2 = 10;
const int global_3 = 20;
volatile char check_data = 0;

char tx_msg[64] = {0};

int main(void){
    int haha;
    int bd = 0;
    Led_Init();
    Usart1_Config();
    Usart1_Init();
    Timer1_Init();
    //I2C_Init();
    Spi1_Init();
    ADC1_TempSensor_Init();
    DMA2_USART1_TX_Init();
    //SPI1_Write(0x0F, 0x80);
    //check_data = Spi1_Read(0x8F);
    
    acb = 10;
    haha = 50;
    printf("bd = %d\n", bd);
    printf("haha = %d\n", haha);
    printf("acb = %d\n", acb);
    printf("check_data = %d\n", check_data);
    printf("global_1 = %d\n", global_1);
    printf("global_2 = %d\n", global_2);
    printf("global_3 = %d\n", global_3);

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

        // read temp
        float temperature = ADC1_ReadTemperature();
        int len = snprintf(tx_msg, sizeof(tx_msg), "Temperature of stm32f411: %.2f C\r\n", temperature);
        DMA2_USART1_TX_Send((uint8_t *)tx_msg, len);
        for (volatile int i = 0; i < 1000000; i++);

    }

    return 0;
}
