#pragma once

#define DG_DEVICE_NAME "Dirgamochi-C3"

// OLED Pins
#define DG_OLED_SDA 21
#define DG_OLED_SCL 20
#define DG_OLED_ADDR 0x3C
#define DG_OLED_WIDTH 128
#define DG_OLED_HEIGHT 64

// TTP223 Touch Buttons
#define DG_TOUCH_TALK 4
#define DG_TOUCH_NEXT 6
#define DG_TOUCH_MODE 7

// I2S Mic (INMP441)
#define DG_MIC_SCK 1
#define DG_MIC_WS  2
#define DG_MIC_SD  8

// I2S Speaker (MAX98357A)
#define DG_SPK_BCLK 1
#define DG_SPK_LRC  2
#define DG_SPK_DIN  5

// Waktu Tekan Tombol
#define DG_BUTTON_DEBOUNCE_MS 50
#define DG_LONG_PRESS_MS 1000
