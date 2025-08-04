// utils.cpp
#include "utils.h"
#include <raylib.h>
#include <raymath.h>

bool allowMove = false;
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};
int cellSize = 30;
int cellCount = 25;
int offset = 75;
double lastUpdateTime = 0;

Color blue = { 72, 116, 191, 255 };
Color red = { 255, 0, 0, 255 }; 
Color darkBlue = { 11, 83, 148, 255 };
Color darkRed = { 200, 0, 0, 255 };

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (Vector2Equals(deque[i], element)) {
            return true;
        }
    }
    return false;
}

bool EventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}