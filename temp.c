// dma.h 
#ifndef DMA_H
#define DMA_H

#include <stdint.h>

/* --- RCC Register --- */
#define RCC_AHB1ENR        (*(volatile uint32_t*)(0x40023830))

/* --- NVIC Register --- */
#define ISER2              (*(volatile uint32_t*)(0x40E00108)) // ISER2 khống chế IRQ 64-95 (DMA2_Stream7 là IRQ 70 -> bit 6)

/* --- USART1 Register --- */
#define USART1_DR          (*(volatile uint32_t*)(0x40011004))
#define USART1_CR3         (*(volatile uint32_t*)(0x40011014))

/* --- DMA2 Registers --- */
#define DMA2_BASE          (0x40026400)
#define DMA2_HISR          (*(volatile uint32_t*)(DMA2_BASE + 0x08))
#define DMA2_HIFCR         (*(volatile uint32_t*)(DMA2_BASE + 0x0C))

/* DMA2 Stream 7 Registers (Offset 0x10 + 0x18 * 7 = 0xB8) */
#define DMA2_S7CR          (*(volatile uint32_t*)(DMA2_BASE + 0xB8))
#define DMA2_S7NDTR        (*(volatile uint32_t*)(DMA2_BASE + 0xBC))
#define DMA2_S7PAR         (*(volatile uint32_t*)(DMA2_BASE + 0xC0))
#define DMA2_S7M0AR        (*(volatile uint32_t*)(DMA2_BASE + 0xC4))

void DMA2_USART1_TX_Init(void);
void DMA2_USART1_TX_Send(uint8_t *src_addr, uint16_t length);

#endif

// dma.c 
#include "dma.h"

void DMA2_USART1_TX_Init(void) {
    // 1. Enable Clock DMA2
    RCC_AHB1ENR |= (1 << 22);

    // 2. Dam bao Stream 7 dang tat truoc khi cau hinh
    DMA2_S7CR &= ~(1 << 0);
    while (DMA2_S7CR & (1 << 0)); // Cho EN bit xac nhan ve 0

    // 3. Xoa toan bo flag ngat cu cua Stream 7 trong HIFCR
    DMA2_HIFCR |= (0x3D << 22); // Clear TCIF7, HTIF7, TEIF7, DMEIF7, FEIF7

    // 4. Cau hinh Stream 7 Control Register (CR)
    DMA2_S7CR &= ~((0x7 << 25) | (0x3 << 6) | (0x3 << 13) | (0x3 << 11)); // Reset CHSEL, DIR, MSIZE, PSIZE
    DMA2_S7CR |= (4 << 25);   // Channel 4
    DMA2_S7CR |= (1 << 6);    // DIR = 01: Memory-to-Peripheral
    DMA2_S7CR |= (1 << 10);   // MINC = 1: Memory address pointer is incremented
    DMA2_S7CR |= (1 << 4);    // TCIE = 1: Transfer complete interrupt enable

    // 5. Gan dia chi ngoai vi (Peripheral Address)
    DMA2_S7PAR = (uint32_t)&USART1_DR;

    // 6. Cho phep ngat DMA2 Stream 7 trong NVIC (IRQ 70: 70 - 64 = bit 6 cua ISER2)
    ISER2 |= (1 << 6);
}

void DMA2_USART1_TX_Send(uint8_t *src_addr, uint16_t length) {
    // Cho DMA hoan thanh luot truyen truoc do (neu co)
    while (DMA2_S7CR & (1 << 0));

    // Clear flag ngat cu
    DMA2_HIFCR |= (0x3D << 22);

    // Cap nhat dia chi bo nho va so luong byte
    DMA2_S7M0AR = (uint32_t)src_addr;
    DMA2_S7NDTR = length;

    // Kich hoat Stream
    DMA2_S7CR |= (1 << 0);
}

// Hàm ngắt xử lý khi hoàn tất truyền DMA
void DMA2_Stream7_IRQHandler(void) {
    // Kiem tra flag TCIF7 (Transfer Complete Interrupt Flag cho Stream 7)
    if (DMA2_HISR & (1 << 27)) {
        DMA2_HIFCR |= (1 << 27); // Clear TCIF7 flag
        
        // Them xu ly sau khi truyen xong tai day (neu can)
    }
}

// dma.c

#include "dma.h"

void DMA2_USART1_TX_Init(void) {
    // 1. Enable Clock DMA2
    RCC_AHB1ENR |= (1 << 22);

    // 2. Dam bao Stream 7 dang tat truoc khi cau hinh
    DMA2_S7CR &= ~(1 << 0);
    while (DMA2_S7CR & (1 << 0)); // Cho EN bit xac nhan ve 0

    // 3. Xoa toan bo flag ngat cu cua Stream 7 trong HIFCR
    DMA2_HIFCR |= (0x3D << 22); // Clear TCIF7, HTIF7, TEIF7, DMEIF7, FEIF7

    // 4. Cau hinh Stream 7 Control Register (CR)
    DMA2_S7CR &= ~((0x7 << 25) | (0x3 << 6) | (0x3 << 13) | (0x3 << 11)); // Reset CHSEL, DIR, MSIZE, PSIZE
    DMA2_S7CR |= (4 << 25);   // Channel 4
    DMA2_S7CR |= (1 << 6);    // DIR = 01: Memory-to-Peripheral
    DMA2_S7CR |= (1 << 10);   // MINC = 1: Memory address pointer is incremented
    DMA2_S7CR |= (1 << 4);    // TCIE = 1: Transfer complete interrupt enable

    // 5. Gan dia chi ngoai vi (Peripheral Address)
    DMA2_S7PAR = (uint32_t)&USART1_DR;

    // 6. Cho phep ngat DMA2 Stream 7 trong NVIC (IRQ 70: 70 - 64 = bit 6 cua ISER2)
    ISER2 |= (1 << 6);
}

void DMA2_USART1_TX_Send(uint8_t *src_addr, uint16_t length) {
    // Cho DMA hoan thanh luot truyen truoc do (neu co)
    while (DMA2_S7CR & (1 << 0));

    // Clear flag ngat cu
    DMA2_HIFCR |= (0x3D << 22);

    // Cap nhat dia chi bo nho va so luong byte
    DMA2_S7M0AR = (uint32_t)src_addr;
    DMA2_S7NDTR = length;

    // Kich hoat Stream
    DMA2_S7CR |= (1 << 0);
}

// Hàm ngắt xử lý khi hoàn tất truyền DMA
void DMA2_Stream7_IRQHandler(void) {
    // Kiem tra flag TCIF7 (Transfer Complete Interrupt Flag cho Stream 7)
    if (DMA2_HISR & (1 << 27)) {
        DMA2_HIFCR |= (1 << 27); // Clear TCIF7 flag
        
        // Them xu ly sau khi truyen xong tai day (neu can)
    }
}

// add uart1.c 
void Usart1_Init(void)
{
    // ... Khởi tạo BRR, CR1, CR2 như code hiện tại của bạn ...

    // Bat chuc nang DMA cho Transmitter (DMAT bit trong USART1_CR3)
    USART1_CR3 |= (1 << 7); // DMAT = 1

    // enable NVIC cho USART1
    ISER1 |= 1 << 5; 
}   