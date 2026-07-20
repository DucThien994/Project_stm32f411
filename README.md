arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -specs=nano.specs -c main.c -o main.o

arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -c main.c -x assembler-with-cpp startup_stm32f411vetx.s -o startup.o

arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -T"STM32F411VETX_FLASH.ld" -Wl,-Map="output.map" -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs -static main.o startup.o -o firmware.elf
