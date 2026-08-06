#define SPI1_BASE_ADDR  0x40013000
#define SPI2_BASE_ADDR  0x40003800

#define SPI1_CR1    (*(volatile uint32_t*)(SPI1_BASE_ADDR + 0x00))
#define SPI1_DR     (*(volatile uint32_t*)(SPI1_BASE_ADDR + 0x0C))
#define SPI1_SR     (*(volatile uint32_t*)(SPI1_BASE_ADDR + 0x08))

void Spi1_Init(void);
char Spi1_Read(char reg_addr);
void SPI1_Write(char reg_addr, char reg_val);