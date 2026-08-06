#define TIM1_BASE_ADDR 0x40010000
#define TIM2_BASE_ADDR 0x40000000

#define TIM1_PSC    (*(volatile uint16_t*)(TIM1_BASE_ADDR + 0x28))
#define TIM1_ARR    (*(volatile uint16_t*)(TIM1_BASE_ADDR + 0x2C))
#define TIM1_CR1    (*(volatile uint16_t*)(TIM1_BASE_ADDR + 0x00))
#define TIM1_DIER   (*(volatile uint16_t*)(TIM1_BASE_ADDR + 0x0C))
#define TIM1_SR     (*(volatile uint16_t*)(TIM1_BASE_ADDR + 0x10))

extern volatile int time_cnt;
void Timer1_Init(void);