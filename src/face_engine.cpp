#include <Arduino.h>
#include "face_engine.h"

FaceEngine::FaceEngine(Adafruit_SSD1306& display) : _display(display) {
    _currentExpr = FACE_NORMAL;
    _lastBlink = 0;
    _isBlinking = false;
}

void FaceEngine::begin() {}

void FaceEngine::setExpression(FaceExpression expr) {
    _currentExpr = expr;
}

void FaceEngine::drawEye(int x, int y, int radius, bool leftEye) {
    if (_isBlinking) {
        _display.drawLine(x - radius, y, x + radius, y, SSD1306_WHITE);
        return;
    }

    switch (_currentExpr) {
        case FACE_NORMAL:
        case FACE_CUTE:
            _display.fillCircle(x, y, radius, SSD1306_WHITE);
            _display.fillCircle(x + (leftEye ? 3 : -3), y - 4, 3, SSD1306_BLACK);
            _display.fillCircle(x + (leftEye ? -3 : 3), y + 4, 1, SSD1306_BLACK);
            if (_currentExpr == FACE_CUTE) {
                _display.drawLine(x - 5, y + radius + 4, x + 5, y + radius + 4, SSD1306_WHITE);
                _display.drawLine(x - 3, y + radius + 6, x + 3, y + radius + 6, SSD1306_WHITE);
            }
            break;
            
        case FACE_HAPPY:
            _display.drawCircle(x, y, radius, SSD1306_WHITE);
            _display.fillRect(x - radius - 1, y, radius * 2 + 2, radius + 1, SSD1306_BLACK);
            break;
            
        case FACE_SLEEPY:
            _display.drawLine(x - radius, y + radius/2, x + radius, y + radius/2, SSD1306_WHITE);
            break;

        case FACE_SURPRISED:
            _display.drawCircle(x, y, radius + 2, SSD1306_WHITE); 
            _display.fillCircle(x, y, 3, SSD1306_WHITE); 
            break;
    }
}

void FaceEngine::drawMouth(int x, int y) {
    if (_currentExpr == FACE_HAPPY || _currentExpr == FACE_NORMAL) {
        _display.drawPixel(x, y, SSD1306_WHITE);
    } else if (_currentExpr == FACE_CUTE) {
        _display.drawLine(x - 2, y - 2, x, y, SSD1306_WHITE);
        _display.drawLine(x, y, x + 2, y - 2, SSD1306_WHITE);
    } else if (_currentExpr == FACE_SURPRISED) {
        _display.drawCircle(x, y + 4, 3, SSD1306_WHITE); 
    }
}

void FaceEngine::update(bool bleConnected, bool hasNotif) {
    _display.clearDisplay();

    if (millis() - _lastBlink > 3000) {
        _isBlinking = true;
        _lastBlink = millis();
    }
    if (_isBlinking && (millis() - _lastBlink > 150)) {
        _isBlinking = false;
        _lastBlink = millis() + random(1000, 4000); 
    }

    drawEye(36, 32, 14, true);
    drawEye(92, 32, 14, false);
    drawMouth(64, 40);

    if (bleConnected) {
        _display.fillCircle(120, 8, 3, SSD1306_WHITE);
    }
    if (hasNotif) {
        _display.setCursor(4, 4);
        _display.print("!");
    }

    _display.display();
}
