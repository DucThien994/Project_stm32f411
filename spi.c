#include "gpio.h"
#include "spi.h"

/*
    3 axis gryroscope i3g4250d
    - spi1 sck : pa5
    - spi1 miso : pa6
    - spi1 mosi : pa7
    - spi1 cs : pe3
*/

void Spi1_Init(void){
    // enable clock 
    uint32_t* RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0x44);
    *RCC_APB2ENR |= 1 << 12; // enable spi1
    uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
    *RCC_AHB1ENR |= 1 << 0; // enable gpio
    *RCC_AHB1ENR |= 1 << 4; // enable gpio

    uint32_t* GPIOA_MODER   = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
    uint32_t* GPIOE_MODER   = (uint32_t*)(GPIOE_BASE_ADDR + 0x00);
    uint32_t* GPIOE_ODR     = (uint32_t*)(GPIOE_BASE_ADDR + 0x14);
    uint16_t* SPI1_CR1      = (uint16_t*)(SPI1_BASE_ADDR + 0x00);

    *GPIOA_MODER &= ~(0b111111 << 10);
    *GPIOA_MODER |= (0b101010 << 10) | (0b10 << 12) | (0b10 << 14); // set alternate function for PA5, PA6, PA7
    *GPIOE_ODR |= 1 << 3; // set pe3 high (inactive)

    // alternate function for PA5, PA6, PA7
    uint32_t* GPIOA_AFRL = (uint32_t*)(GPIOA_BASE_ADDR + 0x20);
    *GPIOA_AFRL &= ~(0xFFF << 20);
    *GPIOA_AFRL |= (0b0101 << 20) | (0b0101 << 24) | (0b0101 << 28);
    
    // pe3 output mode 
    *GPIOE_MODER &= ~(0b11 << 6);
    *GPIOE_MODER |= 1 << 6;

    // config spi
    *SPI1_CR1 |= 1 << 2;
    *SPI1_CR1 |= (0b11 << 3); // 1MHz 
    *SPI1_CR1 |= (1 << 8) | (1 << 9); // Internal slave select , Software slave management
    *SPI1_CR1 |= 1 << 6; // enable SPI

}

char Spi1_Read(char reg_addr){

    uint32_t* GPIOE_ODR = (uint32_t*)(GPIOE_BASE_ADDR + 0x14);
    *GPIOE_ODR &= ~(1 << 3); // pe3 low : active slave 

    uint16_t* SPI1_DR = (uint16_t*)(SPI1_BASE_ADDR + 0x0C);
    uint16_t* SPI1_SR = (uint16_t*)(SPI1_BASE_ADDR + 0x08);

    *SPI1_DR = reg_addr; 
    while(((*SPI1_SR >> 1) & 1) == 0); // wait TXE 
    while(((*SPI1_SR >> 0) & 1) == 0); // wait RXNE
    char dummy_data = *SPI1_DR;
    
    *SPI1_DR = 0xFF; // gửi dummy byte để cấp xung clock cho slave đẩy data
    
    while(((*SPI1_SR >> 1) & 1) == 0); 
    while(((*SPI1_SR >> 0) & 1) == 0);
    char data = *SPI1_DR; // real data 

    // wait BSY = 0
    while(((*SPI1_SR >> 7) & 1) == 1);
    
    *GPIOE_ODR |= 1 << 3; // set pe3 high (inactive slave)

    return data;

}


void SPI1_Write(char reg_addr, char reg_val){

    uint32_t* GPIOE_ODR = (uint32_t*)(GPIOE_BASE_ADDR + 0x14);
	*GPIOE_ODR &= ~(1<<3);	// set PE3 to LOW to active slave
	uint16_t* SPI1_DR = (uint16_t*)(SPI1_BASE_ADDR + 0x0C);
	uint16_t* SPI1_SR = (uint16_t*)(SPI1_BASE_ADDR + 0x08);

    // send address 
	*SPI1_DR = reg_addr;
	while(((*SPI1_SR >> 1) & 1) == 0);
	while(((*SPI1_SR >> 0) & 1) == 0);
    char dummy_data = *SPI1_DR; 

    // send value 
	*SPI1_DR = reg_val;
    while(((*SPI1_SR >> 1) & 1) == 0);
	while(((*SPI1_SR >> 0) & 1) == 0);
	dummy_data = *SPI1_DR;

    // wait SPI free
	while(((*SPI1_SR >> 7)&1)==1);

	*GPIOE_ODR |= (1<<3);	// set PE3 to HIGH to inactive slave

}
