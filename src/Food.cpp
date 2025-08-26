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
#include "Wall.h"

// Khởi tạo biến tĩnh
Texture2D Food::texture;

void Food::LoadTexture() {
    Image image = LoadImage("assets/Graphics/food.png");
    if (image.data == NULL) {
        std::cerr << " Không thể load ảnh food.png!\n";
    }
    texture = LoadTextureFromImage(image); // Tải texture từ ảnh
    UnloadImage(image);
}

void Food::UnloadTexture() {
    ::UnloadTexture(texture);
}

Food::Food(std::deque<Vector2>& snakeBody, const Wall& wall) {
    Image image = LoadImage("assets/Graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    // Tạo vị trí mồi không trùng rắn hoặc tường
    
    position = GenerateRandomPos(snakeBody, wall);  // truyền wall vào đây
}

Food::~Food() {
    // Food::UnloadTexture();
}

void Food::Draw() {
    DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
}

Vector2 Food::GenerateRandomCell() {
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return {x, y};
}

// Vector2 Food::GenerateRandomPos(std::deque<Vector2> snakeBody) {
//     Vector2 pos = GenerateRandomCell();
//     while (ElementInDeque(pos, snakeBody)) {
//         pos = GenerateRandomCell();
//     }
//     return pos;
// }
Vector2 Food::GenerateRandomPos(std::deque<Vector2>& snakeBody, const Wall& wall) {
    Vector2 pos;
    do {
        pos.x = GetRandomValue(0, cellCount - 1);
        pos.y = GetRandomValue(0, cellCount - 1);
    } while (ElementInDeque(pos, snakeBody) || wall.CollidesWith(pos)); // Kiểm tra trùng rắn và tường
    return pos;
}