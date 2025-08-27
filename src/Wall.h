// Wall.h
#ifndef WALL_H
#define WALL_H

#include <vector>
#include <raylib.h>
#include <raymath.h>

class Wall {
public:
    std::vector<Vector2> wallBlocks;  // Vị trí từng khối tường

    Wall();
    void Generate();                  // Sinh tường
    void Draw();                      // Vẽ tường
    // bool CollidesWith(Vector2 pos);  
    bool CollidesWith(Vector2 pos) const; // Kiểm tra rắn đụng tường
};

#endif