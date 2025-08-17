// Game.cpp
#include "Game.h"
#include "utils.h"
#include <raylib.h>
#include <raymath.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// ================== Constructor / Destructor ==================
Game::Game() : snake(), food(snake.body), running(true), score(0), showGameOver(false) {
    InitAudioDevice();
    eatSound = LoadSound("assets/Sounds/eat.mp3");
    wallSound = LoadSound("assets/Sounds/wall.mp3");
}

Game::~Game() {
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}

// ================== Draw ==================
void Game::Draw() {
    ClearBackground(darkBlue);

    DrawText("SNAKE GAME - GROUP 1", offset, offset / 2, 30, green);

    DrawRectangleLinesEx(
        { (float)offset, (float)offset, (float)(cellSize * cellCount), (float)(cellSize * cellCount) },
        3, darkGreen
    );

    // Vẽ leaderboard trực tiếp
    LoadLeaderboard();
    int leaderboardX = offset + cellSize * cellCount + 40;
    int leaderboardY = offset + 20;
    DrawText("Leaderboard (Top 5)", leaderboardX, leaderboardY, 20, darkGreen);

    for (int i = 0; i < std::min(5, (int)leaderboard.size()); i++) {
        std::string entry = std::to_string(i + 1) + ". " +
                            leaderboard[i].name + " - " +
                            std::to_string(leaderboard[i].score);
        DrawText(entry.c_str(), leaderboardX, leaderboardY + 30 + i * 25, 20, darkGreen);
    }

    food.Draw();
    snake.Draw();

    // Overlay Game Over và nút Play Again
    if (showGameOver) {
        int overlayWidth = 300;
        int overlayHeight = 180;
        int overlayX = offset + (cellSize * cellCount - overlayWidth) / 2;
        int overlayY = offset + (cellSize * cellCount - overlayHeight) / 2;
        DrawRectangle(overlayX, overlayY, overlayWidth, overlayHeight, Fade(BLACK, 0.7f));
        DrawText("GAME OVER", overlayX + 60, overlayY + 30, 30, RED);
        DrawText(TextFormat("Score: %d", score), overlayX + 90, overlayY + 80, 20, WHITE);

        // Nút Play Again
        int btnWidth = 150;
        int btnHeight = 40;
        int btnX = overlayX + (overlayWidth - btnWidth) / 2;
        int btnY = overlayY + overlayHeight - btnHeight - 20;
        Rectangle btnRect = { (float)btnX, (float)btnY, (float)btnWidth, (float)btnHeight };
        Vector2 mouse = GetMousePosition();
        Color btnColor = CheckCollisionPointRec(mouse, btnRect) ? GREEN : darkGreen;
        DrawRectangleRec(btnRect, btnColor);
        DrawText("Play Again", btnX + 20, btnY + 10, 20, RAYWHITE);

        // Xử lý click nút Play Again
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, btnRect)) {
            Reset();
        }
    }
}

// ================== Update ==================
void Game::Update() {
    if (running) {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

// ================== Collision ==================
void Game::CheckCollisionWithFood() {
    if (Vector2Equals(snake.body[0], food.position)) {
        food.position = food.GenerateRandomPos(snake.body);
        snake.addSegment = true;
        score++;
        PlaySound(eatSound);
    }
}

void Game::CheckCollisionWithEdges() {
    if (snake.body[0].x == cellCount || snake.body[0].x == -1 ||
        snake.body[0].y == cellCount || snake.body[0].y == -1) {
        GameOver();
    }
}

void Game::CheckCollisionWithTail() {
    std::deque<Vector2> headless = snake.body;
    headless.pop_front();
    if (ElementInDeque(snake.body[0], headless)) {
        GameOver();
    }
}

// ================== Game Over / Reset ==================
void Game::GameOver() {
    SaveScoreToFile();
    showGameOver = true;
    running = false;
    PlaySound(wallSound);
}

void Game::Reset() {
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = true;
    score = 0;
    showGameOver = false;
}

// ================== Leaderboard ==================
void Game::SaveScoreToFile() {
    std::ofstream file("leaderboard.txt", std::ios::app);
    if (file.is_open()) {
        file << playerName << " " << score << "\n";
        file.close();
    }
}

void Game::LoadLeaderboard() {
    leaderboard.clear();
    std::ifstream file("leaderboard.txt");
    std::string line;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int point;
        if (iss >> name >> point) {
            leaderboard.push_back({name, point});
        }
    }

    std::sort(leaderboard.begin(), leaderboard.end(), [](auto& a, auto& b) {
        return a.score > b.score;
    });
}
