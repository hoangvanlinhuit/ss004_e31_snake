// main.cpp
#include <raylib.h>
#include <iostream>
#include "Game.h"
#include "utils.h"


std::string GetPlayerNameInput() {
    std::string name = "";
    int letter = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter your name:", 50, 100, 20, BLACK);
        DrawText(name.c_str(), 50, 140, 20, DARKBLUE);
        EndDrawing();

        if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) name.pop_back();
        for (int key = KEY_A; key <= KEY_Z; key++) {
            if (IsKeyPressed(key)) {
                name += (char)(key + 32); // chuyển sang chữ thường
            }
        }
        if (IsKeyPressed(KEY_ENTER) && !name.empty()) break;
    }
    return name;
}

int main() {

    const int screenWidth = offset * 2 + cellSize * cellCount + 200; // thêm 200 cho leaderboard
    const int screenHeight = offset * 2 + cellSize * cellCount + 50; // thêm chiều cao nếu cần
    InitWindow(screenWidth, screenHeight, "SNAKE GAME - GROUP 1");
    // InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount + 300, "SNAKE GAME - GROUP 1");
    SetTargetFPS(60);
    std::string name = GetPlayerNameInput();

    Game game;
    game.playerName = name;

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (EventTriggered(0.2)) {
            allowMove = true;
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1 && allowMove) {
            game.snake.direction = {0, -1};
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1 && allowMove) {
            game.snake.direction = {0, 1};
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1 && allowMove) {
            game.snake.direction = {-1, 0};
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1 && allowMove) {
            game.snake.direction = {1, 0};
            game.running = true;
            allowMove = false;
        }

        ClearBackground(blue);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);
        DrawText("SNAKE GAME - GROUP 1", offset - 5, 20, 40, darkBlue);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();

        if (game.showPlayAgain && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            int btnX = offset + cellSize * cellCount + 40;
            int btnY = offset + cellSize * 2;
            int btnWidth = 150;
            int btnHeight = 40;

            if (mouse.x >= btnX && mouse.x <= btnX + btnWidth &&
                mouse.y >= btnY && mouse.y <= btnY + btnHeight) {
                game.snake.Reset();
                game.food.position = game.food.GenerateRandomPos(game.snake.body);
                game.running = false;
                game.score = 0;
                game.showPlayAgain = false;
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}