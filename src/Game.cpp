// Game.cpp
#include "Game.h"
#include "utils.h"
#include <raylib.h>
#include <raymath.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Wall.h"


Game::Game() : snake(), food(snake.body, wall), running(true), score(0), showPlayAgain(false) {
    // InitAudioDevice();
    // eatSound = LoadSound("assets/Sounds/eat.mp3");
    // wallSound = LoadSound("assets/Sounds/wall.mp3");

    // Nút "Chơi lại" 3
    showGameOver = false;
    showPlayAgain = false;
    // playAgainButton = { 300, 400, 200, 50 }; // tuỳ chỉnh vị trí và kích thước nút

    // Tao button playAgain can giua
    int buttonWidth = 200;
    int buttonHeight = 50;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    playAgainButton = {
        (float)(screenWidth / 2 - buttonWidth / 2),
        (float)(screenHeight / 2 + 50),  
        (float)buttonWidth,
        (float)buttonHeight
    };
}

Game::~Game() {
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}


void Game::Draw() {
    ClearBackground(darkBlue);

    // Hiển thị màn hình Game Over 
    if (showGameOver) {
        // Nền trắng toàn màn hình
        ClearBackground(WHITE);

        // Hiển thị chữ "GAME OVER"
        DrawText("GAME OVER", GetScreenWidth() / 2 - 120, 200, 40, RED);

        // Hiển thị điểm số
        std::string scoreText = "Score: " + std::to_string(score);
        DrawText(scoreText.c_str(), GetScreenWidth() / 2 - 50, 260, 20, BLACK);

        // Nút Play Again
        DrawRectangleRec(playAgainButton, DARKGRAY);
        // DrawText("Play Again", playAgainButton.x + 30, playAgainButton.y + 15, 20, WHITE);
        int textWidth = MeasureText("Play Again", 20);
        DrawText("Play Again",
                playAgainButton.x + (playAgainButton.width - textWidth) / 2,
                playAgainButton.y + 15,
                20, WHITE);
        

        return;
    }

    // Hiển thị phiên bản game ở góc dưới bên phải
    std::string versionText = "Version 1.0 - Group 1";
    int versionFontSize = 18;
    int versionTextWidth = MeasureText(versionText.c_str(), versionFontSize);
    int versionX = GetScreenWidth() - versionTextWidth - 10;
    int versionY = GetScreenHeight() - versionFontSize - 10;
    DrawText(versionText.c_str(), versionX, versionY, versionFontSize, BLACK);

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

    


    std::string diffText = "Difficulty: ";
    if (difficulty == 0.3f) diffText += "Easy";
    else if (difficulty == 0.2f) diffText += "Normal";
    else if (difficulty == 0.1f) diffText += "Hard";
    else diffText += "Custom";

    DrawText(diffText.c_str(), GetScreenWidth() - 200, 10, 20, LIGHTGRAY);

    // Vẽ rắn và thức ăn trong khung
    food.Draw();
    snake.Draw();
    // Vẽ tường chắn
    wall.Draw();


    // Hien thi do kho o goc ben phai
	diffText = "Difficulty: ";
	if (difficulty == 0.3f) diffText += "Easy";
	else if (difficulty == 0.2f) diffText += "Normal";
	else if (difficulty == 0.1f) diffText += "Hard";
	else diffText += "Custom";
	DrawText(diffText.c_str(), GetScreenWidth() - 200, 10, 20, LIGHTGRAY);

    // hiển thị điểm số
    std::string scoreText = "Score: " + std::to_string(score);
    DrawText(scoreText.c_str(), offset, offset + cellSize * cellCount + 10, 20, GREEN);
}



void Game::Reset() {
    snake.Reset();
    food = Food(snake.body, wall); 
    score = 0;
    showGameOver = false;
    showPlayAgain = false;
    running = true;

    StopMusicStream(bgMusic);
    UnloadMusicStream(bgMusic);
    
    bgMusic = LoadMusicStream("assets/Sounds/background.mp3");
    PlayMusicStream(bgMusic);
    SetMusicVolume(bgMusic, 0.5f);
    isMusicPlaying = true;

}


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
        CheckCollisionWithWall();
    }

    // 
    if (isMusicPlaying) {
        UpdateMusicStream(bgMusic);
    }
    if (IsKeyPressed(KEY_M)) {
        ToggleMusic();
        DrawText(isMusicPlaying ? "Music: ON" : "Music: OFF", offset, 10, 20, GREEN);
    }
}

// Kiểm tra va chạm với thức ăn
void Game::CheckCollisionWithFood() {
    if (Vector2Equals(snake.body[0], food.position)) {
        food.position = food.GenerateRandomPos(snake.body, wall);
        snake.addSegment = true;

        score = score + 10;

        PlaySound(eatSound);
    }
}

// Kiểm tra va chạm với biên
void Game::CheckCollisionWithEdges() {
    if (snake.body[0].x == cellCount || snake.body[0].x == -1 ||
        snake.body[0].y == cellCount || snake.body[0].y == -1) {
        GameOver();
    }
}

// Kiểm tra va chạm với tường
void Game::CheckCollisionWithWall() {
    if (wall.CollidesWith(snake.body[0])) {
        GameOver();
    }
}

// Kiểm tra va chạm với đuôi rắn
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

void Game::Init() {
    InitAudioDevice();  // Khởi tạo hệ thống âm thanh
    bgMusic = LoadMusicStream("assets/Sounds/background.mp3");
    PlayMusicStream(bgMusic);
    SetMusicVolume(bgMusic, 0.5f); // Giảm âm lượng nếu cần
    isMusicPlaying = true; // Reset trạng thái nhạc nền
    eatSound = LoadSound("assets/Sounds/eat.mp3");
    wallSound = LoadSound("assets/Sounds/wall.mp3");
}

void Game::ToggleMusic() {
    isMusicPlaying = !isMusicPlaying;
    if (isMusicPlaying) {
        PlayMusicStream(bgMusic);
    } else {
        PauseMusicStream(bgMusic);
    }
}