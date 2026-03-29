// main.c
#include <stdio.h>
#include <string.h>
#include "hal_mock.h"
#include "secure_engine.h"

// Uygulamaya atlama simülasyonu
void jump_to_application(uint32_t app_entry_point);

int main() {
    printf("\n--- Guvenli Bootloader Simülasyonu v1.0 ---\n\n");

    // Adım 1: Donanımı Hazırla (Mock)
    HAL_Flash_Init();
    HAL_Indicator_Set(LED_OFF);

    // Adım 2: Simülasyon için senaryo hazırla 
    // (Gerçekte bu veri harici bir porttan veya Flash'tan gelir)
    FirmwareImage_t new_update;
    new_update.fw_version = 2; // Yeni versiyon
    new_update.fw_size = 50;  // 50 byte'lik kod
    
    // Gerçek kod simülasyonu (örneğin 0'dan 49'a kadar sayılar)
    for(int i=0; i<50; i++) new_update.fw_binary[i] = i; 
    
    // Geliştirici ortamında bu kodun imzasını oluşturalım (Doğru Senaryo)
    SEC_GenerateMockHash(new_update.fw_binary, new_update.fw_size, new_update.digital_signature);

    printf("[SYSTEM] Yeni yazilim guncellemesi algilandi (v%d).\n", new_update.fw_version);

    // Adım 3: Güvenlik Kritik Kontrol!
    if (SEC_VerifyImageSignature(&new_update)) {
        // BAŞARILI DURUM
        HAL_Indicator_Set(LED_GREEN);
        printf("[SYSTEM] Dogrulama basarili. Flash'a yaziliyor ve sistem boot ediliyor.\n");
        
        // Final kontrolleri ve Flash'ı kilitle
        HAL_Flash_Lock();
        
        // Uygulamaya atla
        jump_to_application(0x08001000); 

    } else {
        // HATA DURUMU (Örneğin bir byte'ı değiştirip dene - imza bozulacaktır)
        HAL_Indicator_Set(LED_RED);
        printf("[ALERT] Kritik Hata: Guvenlik dogrulamasi basarisiz.\n");
        printf("[ALERT] Sistem Guvenli Moda alindi. Boot durduruldu.\n");
        HAL_Flash_Lock(); // Her ihtimale karsi kilitle
    }

    printf("\n--- Simülasyon Sonu ---\n");
    return 0;
}

void jump_to_application(uint32_t app_entry_point) {
    printf("\n[BOOT] Uygulama adresine atlaniyor: 0x%X...\n", app_entry_point);
    printf("[MOCK APP] Kullanici Uygulamasi Calisiyor.\n");
}
