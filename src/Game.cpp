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

    // Nút "Chơi lại" 3
    showGameOver = false;
    showPlayAgain = false;
    playAgainButton = { 300, 400, 200, 50 }; // tuỳ chỉnh vị trí và kích thước nút
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
    // if (showPlayAgain) {
    //     int btnWidth = 150;
    //     int btnHeight = 40;

    //     // Căn giữa trong khung game
    //     int btnX = offset + (cellSize * cellCount - btnWidth) / 2;
    //     int btnY = offset + (cellSize * cellCount - btnHeight) / 2;

    //     Rectangle btnRect = { (float)btnX, (float)btnY, (float)btnWidth, (float)btnHeight };
    //     Vector2 mouse = GetMousePosition();
    //     Color btnColor = CheckCollisionPointRec(mouse, btnRect) ? GREEN : darkGreen;

    //     DrawRectangleRec(btnRect, btnColor);
    //     DrawText("Play Again", btnX + 20, btnY + 10, 20, RAYWHITE);
    // }

    // Hiển thị màn hình Game Over 3
    if (showGameOver) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));
        DrawText("GAME OVER", 320, 200, 40, RED);

        std::string scoreText = "Score: " + std::to_string(score); // Giả sử bạn có biến score
        DrawText(scoreText.c_str(), 350, 250, 20, WHITE);

        DrawRectangleRec(playAgainButton, DARKGRAY);
        DrawText("Play Again", playAgainButton.x + 30, playAgainButton.y + 15, 20, WHITE);
    }

    std::string diffText = "Difficulty: ";
    if (difficulty == 0.3f) diffText += "Easy";
    else if (difficulty == 0.2f) diffText += "Normal";
    else if (difficulty == 0.1f) diffText += "Hard";
    else diffText += "Custom";

    DrawText(diffText.c_str(), GetScreenWidth() - 200, 10, 20, LIGHTGRAY);
    
}

void Game::Reset() {
    snake.Reset();
    food = Food(snake.body);
    score = 0;
    showGameOver = false;
}

// void Game::Update() {
//     if (running) {
//         snake.Update();
//         CheckCollisionWithFood();
//         CheckCollisionWithEdges();
//         CheckCollisionWithTail();
//     }

//     // Xử lý sự kiện chuột cho nút "Chơi lại" 3
//     if (showGameOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePos = GetMousePosition();
//         if (CheckCollisionPointRec(mousePos, playAgainButton)) {
//             Reset(); // Reset lại game (gồm snake, food, score,...)
//             showGameOver = false;
//         }
//     }
// }

void Game::Update() {
    if (running) {
        // Xử lý hướng đi từ bàn phím
        if (IsKeyPressed(KEY_UP) && snake.direction.y != 1) snake.direction = {0, -1};
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1) snake.direction = {0, 1};
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1) snake.direction = {-1, 0};
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1) snake.direction = {1, 0};

        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }

    // Xử lý sự kiện chuột cho nút "Chơi lại" 3
    if (showGameOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        // if (CheckCollisionPointRec(mousePos, playAgainButton)) {
        //     Reset(); // Reset lại game (gồm snake, food, score,...)
        //     showGameOver = false;
        // }
        if (CheckCollisionPointRec(mousePos, playAgainButton)) {
            Reset();              // Reset snake, food, score...
            running = true;       // đặt lại trạng thái game
            showGameOver = false;
            showPlayAgain = false;
        }

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
    SaveScoreToFile();           // Lưu điểm
    running = false;
    PlaySound(wallSound);

    // Bỏ reset snake để hiển thị lại khi chơi lại
    showPlayAgain = true;
    showGameOver = true;
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

