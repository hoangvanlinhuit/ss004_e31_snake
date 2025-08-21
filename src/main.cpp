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
    const int screenWidth = offset * 2 + cellSize * cellCount + 200;
    const int screenHeight = offset * 2 + cellSize * cellCount + 50;
    InitWindow(screenWidth, screenHeight, "SNAKE GAME - GROUP 1");
    SetTargetFPS(60);

    std::string name = GetPlayerNameInput();

    // ====== Menu chọn độ khó ======
    float gameSpeed = 0.2f; // mặc định Normal
    bool difficultyChosen = false;

    Rectangle easyBtn = {(float)screenWidth/2 - 75, 200, 150, 40};
    Rectangle normalBtn = {(float)screenWidth/2 - 75, 260, 150, 40};
    Rectangle hardBtn = {(float)screenWidth/2 - 75, 320, 150, 40};

    while (!WindowShouldClose() && !difficultyChosen) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Select Difficulty", screenWidth/2 - 120, 120, 30, DARKBLUE);

        Vector2 mouse = GetMousePosition();
        DrawRectangleRec(easyBtn, CheckCollisionPointRec(mouse, easyBtn) ? GRAY : LIGHTGRAY);
        DrawRectangleRec(normalBtn, CheckCollisionPointRec(mouse, normalBtn) ? GRAY : LIGHTGRAY);
        DrawRectangleRec(hardBtn, CheckCollisionPointRec(mouse, hardBtn) ? GRAY : LIGHTGRAY);

        DrawText("EASY", easyBtn.x + 40, easyBtn.y + 10, 20, BLACK);
        DrawText("NORMAL", normalBtn.x + 30, normalBtn.y + 10, 20, BLACK);
        DrawText("HARD", hardBtn.x + 40, hardBtn.y + 10, 20, BLACK);

        EndDrawing();

        //Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, easyBtn)) {
                gameSpeed = 0.3f;
                difficultyChosen = true;
            }
            else if (CheckCollisionPointRec(mouse, normalBtn)) {
                gameSpeed = 0.2f;
                difficultyChosen = true;
            }
            else if (CheckCollisionPointRec(mouse, hardBtn)) {
                gameSpeed = 0.1f;
                difficultyChosen = true;
            }
        }
    }

    // ====== Bắt đầu game ======
    Game game;
    game.playerName = name; // Hien thi ten nguoi choi
    game.difficulty = gameSpeed; // Hien thi do kho cua game


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        allowMove = EventTriggered(gameSpeed);  // set flag nếu đủ thời gian
        game.Update();  // trong đó gọi Snake::Update()

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
