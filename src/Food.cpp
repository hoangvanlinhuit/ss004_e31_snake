/*
- Food::Food(...): tạo đối tượng mồi và đặt nó tại vị trí ngẫu nhiên không trùng với thân rắn.
- ~Food(): hủy texture khi đối tượng bị xóa.
- Draw(): vẽ mồi bằng ảnh lên canvas.
- GenerateRandomCell(): tạo 1 vị trí ngẫu nhiên bất kỳ trên lưới ô vuông.
- GenerateRandomPos(...): tạo vị trí ngẫu nhiên đảm bảo không trùng với rắn.
*/

// Food.cpp
#include "Food.h"
#include "utils.h"
#include <iostream>

// Khởi tạo biến tĩnh
Texture2D Food::texture;

void Food::LoadTexture() {
    Image image = LoadImage("assets/Graphics/food.png");
    if (image.data == NULL) {
        std::cerr << " Không thể load ảnh food.png!\n";
    }
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

void Food::UnloadTexture() {
    ::UnloadTexture(texture);
}

Food::Food(std::deque<Vector2> snakeBody) {
    position = GenerateRandomPos(snakeBody);
}

Food::~Food() {
    // Không làm gì cả — không nên huỷ texture dùng chung
}

void Food::Draw() {
    DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
}

Vector2 Food::GenerateRandomCell() {
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return {x, y};
}

Vector2 Food::GenerateRandomPos(std::deque<Vector2> snakeBody) {
    Vector2 pos = GenerateRandomCell();
    while (ElementInDeque(pos, snakeBody)) {
        pos = GenerateRandomCell();
    }
    return pos;
}
