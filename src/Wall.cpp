// Wall.cpp
#include "Wall.h"
#include "utils.h"

Wall::Wall() {
    Generate();  // Gọi hàm sinh tường khi khởi tạo
}

void Wall::Generate() {
    // Ví dụ: tạo viền ngoài làm tường
    wallBlocks.clear();
    for (int i = 0; i < cellCount; i++) {
        wallBlocks.push_back({(float)i, 0}); // trên
        wallBlocks.push_back({(float)i, (float)(cellCount - 1)}); // dưới
        wallBlocks.push_back({0, (float)i}); // trái
        wallBlocks.push_back({(float)(cellCount - 1), (float)i}); // phải
    }

    // Thêm tường bên trong nếu muốn
    wallBlocks.push_back({5, 5});
    wallBlocks.push_back({6, 5});
    wallBlocks.push_back({7, 5});

    wallBlocks.push_back({15, 5});
    wallBlocks.push_back({16, 5});
    wallBlocks.push_back({17, 5});

    wallBlocks.push_back({17, 17});
    wallBlocks.push_back({18, 17});
    wallBlocks.push_back({19, 17});

    wallBlocks.push_back({7, 17});
    wallBlocks.push_back({8, 17});
    wallBlocks.push_back({9, 17});
}

void Wall::Draw() {
    for (Vector2 block : wallBlocks) {
        DrawRectangle(offset + block.x * cellSize, offset + block.y * cellSize, cellSize, cellSize, lightGray);
    }
}

bool Wall::CollidesWith(Vector2 pos) const {
    for (const auto& block : wallBlocks) {
        if (Vector2Equals(block, pos)) return true;
    }
    return false;
}
