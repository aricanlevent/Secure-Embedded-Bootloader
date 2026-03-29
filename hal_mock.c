// hal_mock.c
#include "hal_mock.h"
#include <stdio.h>
#include <string.h>

// Flash belleği simüle eden statik değişken
static uint8_t simulated_flash_memory[8192];
#define FLASH_START_ADDR 0x08000000

void HAL_Flash_Init(void) {
    printf("[HAL] Simule edilen Flash bellek baslatildi...\n");
    memset(simulated_flash_memory, 0, sizeof(simulated_flash_memory));
}

bool HAL_Flash_Read(uint32_t address, void* buffer, uint32_t size) {
    uint32_t internal_offset = address - FLASH_START_ADDR;
    
    printf("[HAL] Flash'tan okunuyor: Adres 0x%X, Boyut %d byte\n", address, size);
    
    if (internal_offset + size > sizeof(simulated_flash_memory)) {
        return false; // Flash sınırları dışında
    }
    
    memcpy(buffer, &simulated_flash_memory[internal_offset], size);
    return true;
}

void HAL_Flash_Lock(void) {
    printf("[HAL] Flash arayuzu donanimsal olarak kilitlendi (Guvenli mod).\n");
}

void HAL_Indicator_Set(LedState_t state) {
    switch(state) {
        case LED_GREEN: printf("[HAL -> LED] YESIL yandi (Sistem Guvenli)\n"); break;
        case LED_RED:   printf("[HAL -> LED] KIRMIZI yanip sonuyor (HATA DETEKTED!)\n"); break;
        default:        printf("[HAL -> LED] Kapali\n"); break;
    }
}
