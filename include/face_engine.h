#pragma once
#include <Adafruit_SSD1306.h>

enum FaceExpression {
    FACE_NORMAL,
    FACE_HAPPY,
    FACE_SLEEPY,
    FACE_CUTE
};

class FaceEngine {
public:
    FaceEngine(Adafruit_SSD1306& display);
    void begin();
    void update(bool bleConnected, bool hasNotif);
    void setExpression(FaceExpression expr);

private:
    Adafruit_SSD1306& _display;
    FaceExpression _currentExpr;
    uint32_t _lastBlink;
    bool _isBlinking;
    
    void drawEye(int x, int y, int radius, bool leftEye);
    void drawMouth(int x, int y);
};
