// common_types.h
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdint.h>

// Simüle edilen yazılımın maksimum boyutu (2KB)
#define FW_MAX_SIZE 2048
// Simüle edilen imza boyutu (örneğin SHA-256 simülasyonu için 32 byte)
#define SIGNATURE_SIZE 32 

// Yazılım Görüntüsü (Firmware Image) Yapısı
typedef struct {
    uint32_t fw_version;                   // Yazılım versiyonu
    uint32_t fw_size;                      // Binary boyutu
    uint8_t  fw_binary[FW_MAX_SIZE];        // Gerçek kod (raw binary)
    uint8_t  digital_signature[SIGNATURE_SIZE]; // Doğrulama imzası
} FirmwareImage_t;

#endif // COMMON_TYPES_H
