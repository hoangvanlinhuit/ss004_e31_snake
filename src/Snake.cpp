// Snake.cpp
#include "Snake.h"
#include "utils.h"
#include <raymath.h>

Snake::Snake() : body({{6, 9}, {5, 9}, {4, 9}}), direction({1, 0}), addSegment(false) {}

void Snake::Draw() {
    for (unsigned int i = 0; i < body.size(); i++) {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = {offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize};
        DrawRectangleRounded(segment, 0.5, 6, darkGreen);
    }
}

void Snake::Update() {
    body.push_front(Vector2Add(body[0], direction));
    if (addSegment) addSegment = false;
    else body.pop_back();
}

void Snake::Reset() {
    body = {{6, 9}, {5, 9}, {4, 9}};
    direction = {1, 0};
}
