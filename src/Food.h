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

// Thu vien deque dung de luu vi tri cac o (thay the vector)
#include <deque>

// Dinh nghia lop Food (doi tuong moi trong game)
class Food {
public:
    Vector2 position;       // Vi tri hien tai cua moi
    Texture2D texture;      // Hinh anh texture cua moi

    // Ham khoi tao, nhan vao than cua ran de tao vi tri moi khong trung
    Food(std::deque<Vector2> snakeBody);

    // Ham huy doi tuong, giai phong texture
    ~Food();

    // Ham ve moi len man hinh
    void Draw();

    // Ham tao mot toa do ngau nhien trong luoi
    Vector2 GenerateRandomCell();

    // Ham tao vi tri moi khong trung voi vi tri cua ran
    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody);
};

#endif
