// Food.h
#ifndef FOOD_H
#define FOOD_H
#include <raylib.h>
#include <deque>

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> snakeBody);
    ~Food();
    void Draw();
    Vector2 GenerateRandomCell();
    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody);
};

#endif