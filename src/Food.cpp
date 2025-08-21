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

// Ham khoi tao doi tuong Food, nhan vao body cua con ran
Food::Food(std::deque<Vector2> snakeBody) {
    // Tai anh chuot tu file PNG

    Image image = LoadImage("assets/Graphics/food.png");


    // Chuyen anh thanh texture de ve len man hinh
    texture = LoadTextureFromImage(image);

    // Giai phong bo nho anh sau khi da tao texture
    UnloadImage(image);

    // Tao vi tri ngau nhien cho moi, khong trung voi vi tri cua ran
    position = GenerateRandomPos(snakeBody);
}

// Ham huy doi tuong Food, giai phong texture
Food::~Food() {
    UnloadTexture(texture);
}

// Ham ve moi len man hinh tai vi tri hien tai
void Food::Draw() {
    // Ve texture tai vi tri moi (canh le + toa do x, y * kich thuoc o)
    DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
}

// Ham tao vi tri ngau nhien tren luoi o vuong
Vector2 Food::GenerateRandomCell() {
    float x = GetRandomValue(0, cellCount - 1); // Gia tri x ngau nhien
    float y = GetRandomValue(0, cellCount - 1); // Gia tri y ngau nhien
    return {x, y}; // Tra ve toa do Vector2
}

// Ham tao vi tri moi khong trung voi than con ran
Vector2 Food::GenerateRandomPos(std::deque<Vector2> snakeBody) {
    Vector2 pos = GenerateRandomCell(); // Khoi tao vi tri ngau nhien
    while (ElementInDeque(pos, snakeBody)) {
        // Neu vi tri trung voi ran thi tao lai
        pos = GenerateRandomCell();
    }
    return pos; // Tra ve vi tri hop le
}
