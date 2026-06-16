INCLUDE_PATHS = -I ./include \
				-I ./STM32F4xx

CC = arm-none-eabi-gcc

CFLAGS += 	-DSTM32F411xE \
			-mcpu=cortex-m4 \
			-I ./Include \
			-I ./STM32F4xx\
			-I STM32F4xx\ 
			-I

%.o: %.c
	$(CC) %	$(CFLAGS) -c $< -o $@

