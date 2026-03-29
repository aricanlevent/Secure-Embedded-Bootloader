// hal_mock.h
#ifndef HAL_MOCK_H
#define HAL_MOCK_H

#include "common_types.h"
#include <stdbool.h>

// Mock Flash arayüzü
void HAL_Flash_Init(void);
bool HAL_Flash_Read(uint32_t address, void* buffer, uint32_t size);
void HAL_Flash_Lock(void); // Flash'ı güvenli hale getir

// Mock LED/Durum göstergesi
typedef enum { LED_GREEN, LED_RED, LED_OFF } LedState_t;
void HAL_Indicator_Set(LedState_t state);

#endif // HAL_MOCK_H
