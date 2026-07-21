#include <stdint.h>

#define GPIOB_BASE_ADDR (*(volatile uint32_t*)(0x40020400))
#define GPIOA_BASE_ADDR (*(volatile uint32_t*)(0x40020000))
#define GPIOC_BASE_ADDR (*(volatile uint32_t*)(0x40020800))
#define GPIOD_BASE_ADDR (*(volatile uint32_t*)(0x40020C00))
#define I2C1_BASE_ADDR (*(volatile uint32_t*)(0x40005400))
#define I2C2_BASE_ADDR (*(volatile uint32_t*)(0x40005800))
#define I2C3_BASE_ADDR (*(volatile uint32_t*)(0x40005C00))
#define DMA1_BASE_ADDR (*(volatile uint32_t*)(0x40026000))
#define EXTI_BASE_ADDR (*(volatile uint32_t*)(0x40013C00))
#define SPI1_BASE_ADDR (*(volatile uint32_t*)(0x40013000))
#define RCC_BASE_ADDR (*(volatile uint32_t*)(0x40023800))


typedef enum{
	// dat dung theo thu tu cua schematic
	LED_GREEN,
	LED_ORANGE,
	LED_RED,
	LED_BLUE,
}led_t;

typedef enum{
	OFF_LED,
	ON_LED,
}led_state_t;

void Led_Init();
void LedCtrl(led_t led, led_state_t state);
void Button_Init();
char Button_Get_State();