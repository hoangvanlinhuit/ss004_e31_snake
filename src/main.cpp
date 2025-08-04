// main.cpp
#include <raylib.h>
#include <iostream>
#include "Game.h"
//#include "utils.h"

using namespace std;

int main() {
    cout << "SNAKE GAME - GROUP 1" << endl;
    InitWindow(750, 750, "SNAKE GAME - GROUP 1");
    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        BeginDrawing();

        

        EndDrawing();
    }
    CloseWindow();
    return 0;
}