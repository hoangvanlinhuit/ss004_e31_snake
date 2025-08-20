// Game.cpp
#include "Game.h"
#include "utils.h"
#include <raylib.h>
#include <raymath.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>



Game::Game() : snake(), food(snake.body), running(true), score(0), showPlayAgain(false) {
    InitAudioDevice();
    eatSound = LoadSound("assets/Sounds/eat.mp3");
    wallSound = LoadSound("assets/Sounds/wall.mp3");
}

Game::~Game() {
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}

void Game::Draw() {
    ClearBackground(darkBlue);

    // Tiêu đề
    DrawText("SNAKE GAME - GROUP 1", offset, offset / 2, 30, green);

    // Vẽ khung chơi game (canvas)
    DrawRectangleLinesEx(
        { (float)offset, (float)offset, (float)(cellSize * cellCount), (float)(cellSize * cellCount) },
        3, darkGreen
    );

    

    // Load leaderboard từ file mỗi lần vẽ
    LoadLeaderboard();

    // Vẽ Leaderboard bên phải canvas
    int leaderboardX = offset + cellSize * cellCount + 40;
    int leaderboardY = offset + 20;
    DrawText("Leaderboard (Top 5)", leaderboardX, leaderboardY, 20, darkGreen);

    for (int i = 0; i < std::min(5, (int)leaderboard.size()); i++) {
        std::string entry = std::to_string(i + 1) + ". " + leaderboard[i].name + " - " + std::to_string(leaderboard[i].score);
        DrawText(entry.c_str(), leaderboardX, leaderboardY + 30 + i * 25, 20, darkGreen);
    }

    // Vẽ rắn và thức ăn trong khung
    food.Draw();
    snake.Draw();

    // Vẽ nút trong Draw() nếu showPlayAgain == true
    if (showPlayAgain) {
        int btnWidth = 150;
        int btnHeight = 40;

        // Căn giữa trong khung game
        int btnX = offset + (cellSize * cellCount - btnWidth) / 2;
        int btnY = offset + (cellSize * cellCount - btnHeight) / 2;

        Rectangle btnRect = { (float)btnX, (float)btnY, (float)btnWidth, (float)btnHeight };
        Vector2 mouse = GetMousePosition();
        Color btnColor = CheckCollisionPointRec(mouse, btnRect) ? GREEN : darkGreen;

        DrawRectangleRec(btnRect, btnColor);
        DrawText("Play Again", btnX + 20, btnY + 10, 20, RAYWHITE);
    }

    
}

void Game::Update() {
    if (running) {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

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

void Game::GameOver() {
    SaveScoreToFile();  // Ghi điểm trước khi reset
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    score = 0;
    PlaySound(wallSound);
    showPlayAgain = true;  // Hiển thị nút "Chơi lại" sau khi thua
}

void Game::SaveScoreToFile() {
    std::ofstream file("leaderboard.txt", std::ios::app);  // Ghi tiếp vào file
    if (file.is_open()) {
        file << playerName << " " << score << "\n";
        file.close();
    }
}

void Game::ShowLeaderboard() {
    std::ifstream file("leaderboard.txt");
    std::vector<std::pair<std::string, int>> scores;
    std::string line;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int point;
        if (iss >> name >> point) {
            scores.push_back({name, point});
        }
    }

    // Sắp xếp giảm dần theo điểm
    std::sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    int y = offset;
    DrawText("Leaderboard (Top 5)", offset + 400, y, 20, darkGreen);
    y += 30;

    for (size_t i = 0; i < std::min(size_t(5), scores.size()); ++i) {
        DrawText(TextFormat("%d. %s - %d", i + 1, scores[i].first.c_str(), scores[i].second),
                 offset + 400, y, 20, darkGreen);
        y += 30;
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