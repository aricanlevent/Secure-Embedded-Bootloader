// secure_engine.h
#ifndef SECURE_ENGINE_H
#define SECURE_ENGINE_H

#include "common_types.h"
#include <stdbool.h>

// Yazılım binary'sinin basit bir hash'ini oluşturur (Gerçek SHA yerine basit XOR sum)
void SEC_GenerateMockHash(const uint8_t* data, uint32_t size, uint8_t* output_hash);

// Yazılım görüntüsünün imzasını, sistemdeki anahtarla doğrular
bool SEC_VerifyImageSignature(const FirmwareImage_t* image);

#endif // SECURE_ENGINE_H
