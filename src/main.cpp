#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ChronosESP32.h>
#include "dirgamochi_config.h"
#include "face_engine.h"
#include "audio_engine.h"

Adafruit_SSD1306 display(DG_OLED_WIDTH, DG_OLED_HEIGHT, &Wire, -1);
ChronosESP32 chronos(DG_DEVICE_NAME);
FaceEngine face(display);
AudioEngine audio;

volatile bool bleConnected = false;
volatile bool newNotification = false;

struct Button {
    uint8_t pin;
    bool last = false;
    uint32_t pressedAt = 0;
    bool longSent = false;

    Button(uint8_t p) : pin(p) {}

    void begin() {
        pinMode(pin, INPUT); 
        last = digitalRead(pin);
    }

    bool shortPress() {
        bool now = digitalRead(pin);
        bool event = false;
        if (now && !last) {
            pressedAt = millis();
            longSent = false;
        }
        if (!now && last) {
            uint32_t held = millis() - pressedAt;
            if (held >= DG_BUTTON_DEBOUNCE_MS && held < DG_LONG_PRESS_MS) {
                event = true;
            }
        }
        last = now;
        return event;
    }
};

Button talkBtn{DG_TOUCH_TALK};
Button nextBtn{DG_TOUCH_NEXT};
Button modeBtn{DG_TOUCH_MODE};

void connectionCallback(bool state) {
    bleConnected = state;
    Serial.printf("[Chronos] %s\n", state ? "CONNECTED" : "DISCONNECTED");
}

void notificationCallback(Notification n) {
    newNotification = true;
    Serial.printf("[Notif] %s: %s\n", n.title.c_str(), n.message.c_str());
    face.setExpression(FACE_SURPRISED); 
}

void setup() {
    Serial.begin(115200);
    delay(3000); 

    Serial.println("Starting Dirgamochi-C3...");

    talkBtn.begin();
    nextBtn.begin();
    modeBtn.begin();

    Wire.begin(DG_OLED_SDA, DG_OLED_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, DG_OLED_ADDR)) {
        Serial.println("OLED Failed!");
        while(true) delay(100);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 30);
    display.print("Wake up...");
    display.display();
    delay(1000);

    face.begin();
    audio.begin();

    chronos.setConnectionCallback(connectionCallback);
    chronos.setNotificationCallback(notificationCallback);
    chronos.begin();

    Serial.println("Ready.");
}

void loop() {
    chronos.loop();

    if (nextBtn.shortPress()) {
        face.setExpression(FACE_CUTE);
        Serial.println("NEXT Pressed -> CUTE mode");
    }

    if (modeBtn.shortPress()) {
        face.setExpression(FACE_HAPPY);
        Serial.println("MODE Pressed -> HAPPY mode");
    }

    if (talkBtn.shortPress()) {
        face.setExpression(FACE_NORMAL);
        Serial.println("TALK Pressed -> NORMAL mode");
    }

    face.update(bleConnected, chronos.getNotificationCount() > 0);
    delay(10);
}
