CC      = arm-none-eabi-gcc
CPU     = -mcpu=cortex-m4
LDSCRIPT = STM32F411VETX_FLASH.ld

CFLAGS  = $(CPU) -std=gnu11 -specs=nano.specs -MMD -MP
LDFLAGS = $(CPU) -std=gnu11 -T$(LDSCRIPT) -Wl,-Map=output.map -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs -static

SRCS    = main.c gpio.c usart1.c timer1.c i2c.c spi.c
OBJS    = $(SRCS:.c=.o) startup.o
DEPS    = $(SRCS:.c=.d)
TARGET  = firmware.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

startup.o: startup_stm32f411vetx.s
	$(CC) $(CPU) -std=gnu11 -x assembler-with-cpp -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) output.map

.PHONY: all clean
