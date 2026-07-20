## 1. Compile (.c/.s -> .o)

arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -specs=nano.specs -c main.c -o main.o

arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -specs=nano.specs -c gpio.c -o gpio.o

arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -specs=nano.specs -c usart1.c -o usart1.o

arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -x assembler-with-cpp -c startup_stm32f411vetx.s -o startup.o

## 2. Link (.o -> .elf)

arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -TSTM32F411VETX_FLASH.ld -Wl,-Map=output.map -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs -static main.o gpio.o usart1.o startup.o -o firmware.elf

## 3. Convert (.elf -> .hex / .bin)

arm-none-eabi-objcopy -O ihex firmware.elf firmware.hex

arm-none-eabi-objcopy -O binary firmware.elf firmware.bin

## 4. Flash (nạp vào chip)

Dùng 1 trong các cách sau tùy công cụ debug probe:

st-flash write firmware.bin 0x8000000

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program firmware.elf verify reset exit"

STM32_Programmer_CLI -c port=SWD -w firmware.hex -v -rst
