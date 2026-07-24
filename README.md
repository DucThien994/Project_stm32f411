# STM32F411 Bare-Metal Peripheral Drivers

[![Platform](https://img.shields.io/badge/MCU-STM32F411VET6-03234B?logo=stmicroelectronics&logoColor=white)](https://www.st.com/en/microcontrollers-microprocessors/stm32f411.html)
[![Toolchain](https://img.shields.io/badge/Toolchain-arm--none--eabi--gcc-informational)](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
[![Language](https://img.shields.io/badge/Language-C%20(gnu11)-blue)](#)
[![Style](https://img.shields.io/badge/Style-Register--Level%20%2F%20No%20HAL-orange)](#)
[![Status](https://img.shields.io/badge/Status-In%20Progress-yellow)](#)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

> Register-level (no HAL, no CMSIS driver layer) firmware for the **STM32F411E-Discovery** board, written from the datasheet and reference manual up. Built to deeply understand the peripherals a typical embedded/firmware internship expects: GPIO, EXTI-style polling, USART, general-purpose timers, I2C, and SPI — driving a real SPI sensor (I3G4250D 3-axis gyroscope) end to end.

<p align="center">
  <!-- Once you have a capture, drop it at docs/images/demo.gif and uncomment the line below -->
  <!-- <img src="docs/images/demo.gif" alt="Demo: button-triggered LEDs and UART heartbeat on the STM32F411E-Discovery" width="600"> -->
  <sub>📸 Board photo / demo GIF goes here — see <a href="#-demo">Demo</a> for how to add it.</sub>
</p>

---

## Table of Contents

- [Why This Project](#why-this-project)
- [Hardware](#hardware)
- [Features](#features)
- [Demo](#-demo)
- [Repository Structure](#repository-structure)
- [Peripheral Drivers](#peripheral-drivers)
- [Getting Started](#getting-started)
- [Wiring](#wiring)
- [What I Learned](#what-i-learned)
- [Roadmap](#roadmap)
- [Author](#author)
- [🇻🇳 Tiếng Việt](#-tiếng-việt)

## Why This Project

Most beginner STM32 projects lean on STM32CubeMX and the HAL, which is great for productivity but hides exactly the mechanics an embedded internship interview asks about: clock enables, register bit-fields, alternate-function mapping, and polled status flags. This repository is my deliberate practice at writing every driver **directly against the STM32F411 reference manual (RM0383)**, so I can explain *why* each register write is there, not just that it works.

## Hardware

| Item | Detail |
|---|---|
| Board | STM32F411E-Discovery |
| MCU | STM32F411VET6 — Arm Cortex-M4, 512 KB Flash, 128 KB RAM |
| External sensor | I3G4250D — 3-axis digital gyroscope (SPI) |
| Toolchain | `arm-none-eabi-gcc`, GNU Make, raw linker script (no CubeIDE project needed) |
| Debug/flash | ST-LINK (on-board)  STM32CubeProgrammer |

## Features

- **GPIO** — direct `MODER`/`ODR`/`IDR` register control for the 4 on-board LEDs (green, orange, red, blue) and the user button, no library calls.
- **USART1** — polled TX driver used as a debug/telemetry console (`USART_SendString`).
- **TIM1** — free-running millisecond tick (`time_cnt`) used to pace the main loop without blocking `delay()` calls.
- **I2C1** — single-byte register read/write driver (`I2C_ReadData` / `I2C_WriteData`) for I2C sensors/EEPROMs.
- **SPI1** — full-duplex driver, software slave-select, used to talk to a real **I3G4250D 3-axis gyroscope**.
- **Application loop** — button press drives all 4 LEDs, and a heartbeat string is streamed over UART every ~1 second using the timer tick, demonstrating non-blocking scheduling on bare metal.

## 🎬 Demo

> _Add a short GIF or photo here once captured — e.g. board LEDs responding to the button press, and a terminal (PuTTY / minicom / `screen`) showing the UART heartbeat._

```
docs/
└── images/
    └── demo.gif   <- drop your capture here, this README already links to it
```

## Repository Structure

```
Project_stm32f411/
├── main.c                        # Application entry point / main loop
├── gpio.c / gpio.h                # LED + button register-level driver
├── usart1.c / usart1.h            # USART1 polled TX driver
├── timer1.c / timer1.h            # TIM1 millisecond tick
├── i2c.c / i2c.h                  # I2C1 byte read/write driver
├── spi.c / spi.h                  # SPI1 driver (I3G4250D gyroscope)
├── startup_stm32f411vetx.s        # Reset handler + vector table
├── STM32F411VETX_FLASH.ld         # Linker script (512K Flash / 128K RAM)
└── Makefile                       # Build system (arm-none-eabi-gcc)
```

## Peripheral Drivers

| Module | Pins Used | Key Registers Touched | Public API |
|---|---|---|---|
| GPIO / LED | PD12–PD15 (LEDs), PA0 (button) | `RCC_AHB1ENR`, `GPIOx_MODER`, `GPIOx_ODR`, `GPIOx_IDR` | `Led_Init`, `LedCtrl`, `Button_Init`, `Button_Get_State` |
| USART1 | PA9 (TX) | `RCC_APB2ENR`, `USART1_BRR/CR1/SR/DR` | `Usart1_Config`, `Usart1_Init`, `USART_SendChar`, `USART_SendString` |
| TIM1 | — (internal) | `RCC_APB2ENR`, `TIM1_PSC/ARR/CR1/DIER` | `Timer1_Init`, `time_cnt` |
| I2C1 (LSM303AGR) | PB6 (SCL), PB9 (SDA) | `RCC_APB1ENR`, `I2C1_CR1/CR2/SR1/SR2/DR` | `I2C_Init`, `I2C_ReadData`, `I2C_WriteData` |
| SPI1 (I3G4250D) | PA5 (SCK), PA6 (MISO), PA7 (MOSI), PE3 (CS) | `RCC_APB2ENR`, `RCC_AHB1ENR`, `GPIOA_MODER/AFRL`, `SPI1_CR1/SR/DR` | `Spi1_Init`, `Spi1_Read`, `SPI1_Write` |

## Getting Started

### Prerequisites

- [`arm-none-eabi-gcc`](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) toolchain on your `PATH`
- `make`
- ST-LINK utilities for flashing: [`st-flash`](https://github.com/stlink-org/stlink) or [OpenOCD](https://openocd.org/) / STM32CubeProgrammer

### Build

```bash
git clone https://github.com/DucThien994/Project_stm32f411.git
cd Project_stm32f411
make
```

This produces `firmware.elf` plus a linker `output.map`. To rebuild from scratch:

```bash
make clean && make
```

### Flash

Using `st-flash` (convert the ELF to binary first):

```bash
arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
st-flash write firmware.bin 0x08000000
```

Or load `firmware.elf` directly with OpenOCD / STM32CubeProgrammer over the on-board ST-LINK.

### Observe

Open a serial terminal at **115200 8N1** on the ST-LINK VCP port to see the UART heartbeat, and press the user button (PA0) to light up all four LEDs.

## Wiring

I3G4250D gyroscope over SPI1 (as used in `spi.c`):

| Signal | MCU Pin |
|---|---|
| SCK | PA5 |
| MISO | PA6 |
| MOSI | PA7 |
| CS (software-controlled) | PE3 |

## What I Learned

This project was built as hands-on preparation for an embedded/firmware internship, so the goal was understanding, not just a working `.elf`:

- Reading and applying the **RM0383 reference manual** directly — RCC clock gating, GPIO alternate-function mapping, and peripheral status-flag polling — instead of relying on HAL abstractions.
- The difference between **blocking delay loops and tick-based scheduling** (`TIM1` driving `time_cnt`), and why the latter is necessary once multiple peripherals share the main loop.
- Debugging real SPI transactions against a physical sensor (I3G4250D): read/write register framing, chip-select timing, and verifying `SPI_SR` flags (`BSY`, `TXE`, `RXNE`) instead of assuming timing "just works."
- Structuring firmware into per-peripheral modules (`gpio`, `usart1`, `timer1`, `i2c`, `spi`) with clean headers, so the codebase stays readable as more drivers are added.
- Using `git` deliberately during development (see commit history) to isolate each peripheral bring-up as its own reviewable step.

## Roadmap

- [ ] Move I2C/SPI/USART drivers from polling to interrupt-driven (NVIC)
- [ ] Add a proper I3G4250D application layer (WHO_AM_I check, angular-rate conversion, unit tests for parsing)
- [ ] Add a `docs/` folder with wiring diagrams and a captured demo GIF
- [ ] Add basic unit tests for register-manipulation helpers using a host-side mock
- [ ] CI build check (GitHub Actions) running `make` with `arm-none-eabi-gcc`

## Author

**Nguyen Duc Thien**
📧 ndthien994@gmail.com
🔗 [github.com/DucThien994](https://github.com/DucThien994)

If you're reviewing this as part of an internship application: thank you for taking the time — feedback and code review comments are very welcome via GitHub Issues.

---

## 🇻🇳 Tiếng Việt

**STM32F411 Bare-Metal Peripheral Drivers** là project firmware viết trực tiếp ở mức thanh ghi (không dùng HAL/CubeMX) cho board **STM32F411E-Discovery**, nhằm hiểu sâu cách hoạt động của các ngoại vi thường gặp khi phỏng vấn/thực tập embedded: GPIO, USART, Timer, I2C và SPI — điều khiển thực tế một cảm biến con quay hồi chuyển 3 trục **I3G4250D** qua SPI.

**Vì sao làm project này:** phần lớn project STM32 cho người mới dùng CubeMX + HAL, giúp code nhanh nhưng che mất cơ chế bên dưới (bật clock, cấu hình thanh ghi, alternate function, cờ trạng thái...) — những thứ nhà tuyển dụng thường hỏi khi phỏng vấn thực tập embedded. Project này được viết trực tiếp theo **reference manual RM0383** để hiểu rõ *vì sao* từng dòng cấu hình thanh ghi lại cần thiết.

**Tính năng chính:**
- Điều khiển 4 LED và đọc nút nhấn bằng thanh ghi GPIO thuần.
- Gửi dữ liệu debug qua USART1 (polling).
- Tạo tick 1ms bằng TIM1, dùng để lập lịch vòng lặp chính không cần `delay()` chặn CPU.
- Driver I2C1 đọc/ghi thanh ghi 1 byte.
- Driver SPI1 giao tiếp thực với cảm biến I3G4250D (3-axis gyroscope).

**Build & nạp firmware:**
```bash
make                       # biên dịch ra firmware.elf
arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
st-flash write firmware.bin 0x08000000
```

**Những gì tôi học được:** đọc và áp dụng datasheet/reference manual thay vì phụ thuộc HAL; phân biệt vòng lặp delay chặn CPU và lập lịch theo tick timer; debug giao tiếp SPI thật với cảm biến (khung lệnh đọc/ghi thanh ghi, thời gian chip-select, kiểm tra cờ trạng thái `BSY/TXE/RXNE`); tổ chức code theo từng module ngoại vi rõ ràng, dễ mở rộng.

📧 Liên hệ: ndthien994@gmail.com — mọi góp ý về code đều được hoan nghênh.
