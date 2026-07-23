#define SPI1_BASE_ADDR  0x40013000
#define SPI2_BASE_ADDR  0x40003800

void Spi1_Init(void);
char Spi1_Read(char reg_addr);
void SPI1_Write(char reg_addr, char reg_val);