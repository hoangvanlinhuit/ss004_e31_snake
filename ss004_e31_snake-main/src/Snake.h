// Snake.h
#ifndef SNAKE_H
#define SNAKE_H
#include <deque>
#include <raylib.h>

class Snake {
public:
    std::deque<Vector2> body;
    Vector2 direction;
    bool addSegment;

    Snake();
    void Draw();
    void Update();
    void Reset();
};

#endif