// secure_engine.c
#include "secure_engine.h"
#include <stdio.h>
#include <string.h>

// Sistem Boot ROM'unda saklanan simüle edilmiş bir Public Key
const uint8_t MOCK_SYSTEM_PUBLIC_KEY[SIGNATURE_SIZE] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
    0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0xC0 // Sonuncu farkli
};

void SEC_GenerateMockHash(const uint8_t* data, uint32_t size, uint8_t* output_hash) {
    // 3. sinif seviyesinde basit bir XOR-tabanli hash simülasyonu
    memset(output_hash, 0, SIGNATURE_SIZE);
    for(uint32_t i = 0; i < size; i++) {
        output_hash[i % SIGNATURE_SIZE] ^= data[i];
    }
    // Biraz daha karistiralim (Public Key ile XOR)
    for(int i=0; i<SIGNATURE_SIZE; i++) {
        output_hash[i] ^= MOCK_SYSTEM_PUBLIC_KEY[i];
    }
}

bool SEC_VerifyImageSignature(const FirmwareImage_t* image) {
    printf("[SECURE] Yazilim imzasi dogrulaniyor...\n");
    uint8_t calculated_hash[SIGNATURE_SIZE];
    
    // 1. Binary'nin hash'ini hesapla
    SEC_GenerateMockHash(image->fw_binary, image->fw_size, calculated_hash);

    // 2. Hesaplanan hash'i, imajın içindeki imzayla karşılaştır
    if (memcmp(calculated_hash, image->digital_signature, SIGNATURE_SIZE) == 0) {
        printf("[SECURE] Imza GECERLI! Yazilim guvenilir.\n");
        return true;
    } else {
        printf("[SECURE] Imza GECERSİZ! Bozulmus veya yetkisiz yazilim.\n");
        return false;
    }
}
