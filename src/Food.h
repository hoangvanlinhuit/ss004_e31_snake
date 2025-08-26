/*
- Food(...): khởi tạo con mồi và chọn vị trí ban đầu không trùng rắn.
- ~Food(): giải phóng tài nguyên đồ họa (texture).
- Draw(): vẽ mồi lên khung game tại vị trí hiện tại.
- GenerateRandomCell(): tạo một ô bất kỳ.
- GenerateRandomPos(...): tìm ô hợp lệ (không trùng thân rắn).
*/

// Food.h
#ifndef FOOD_H
#define FOOD_H

// Thu vien raylib dung de ve do hoa
#include <raylib.h>
#include "Wall.h" 

// Thu vien deque dung de luu vi tri cac o (thay the vector)
#include <deque>

class Food {
public:
    static Texture2D texture;  // dùng chung
    static void LoadTexture();
    static void UnloadTexture();

    Vector2 position;
    Food(std::deque<Vector2>& snakeBody, const Wall& wall);
    ~Food();
    void Draw();
    Vector2 GenerateRandomCell();
    // Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody);
    Vector2 GenerateRandomPos(std::deque<Vector2>& snakeBody, const Wall& wall); // Thêm wall
};

#endif
