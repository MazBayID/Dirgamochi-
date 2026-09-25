#include "audio_engine.h"
#include "dirgamochi_config.h"

void AudioEngine::begin() {
    // I2S init bisa memicu crash jika RAM sisa sedikit. 
    // Kita deklarasikan pinnya saja dulu untuk memastikan aman.
    pinMode(DG_MIC_SD, INPUT); 
    Serial.println("[Audio] Engine disiapkan, I2S di-bypass untuk stabilitas.");
}

void AudioEngine::playBeep() {
    // Logic mainkan suara via MAX98357A nanti ditaruh di sini
}
