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


    // Nút "Choi l?i" 3
    showGameOver = false;
    showPlayAgain = false;
    // playAgainButton = { 300, 400, 200, 50 }; // tu? ch?nh v? trí và kích thu?c nút


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


    // Hi?n th? màn hình Game Over
    if (showGameOver) {
        // N?n tr?ng toàn màn hình
        ClearBackground(WHITE);


        // Hi?n th? ch? "GAME OVER"
        DrawText("GAME OVER", GetScreenWidth() / 2 - 120, 200, 40, RED);


        // Hi?n th? di?m s?
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


    // Tiêu d?
    DrawText("SNAKE GAME - GROUP 1", offset, offset / 2, 30, green);


    // V? khung choi game (canvas)
    DrawRectangleLinesEx(
        { (float)offset, (float)offset, (float)(cellSize * cellCount), (float)(cellSize * cellCount) },
        3, darkGreen
    );
   
    // Load leaderboard t? file m?i l?n v?
    LoadLeaderboard();


    // V? Leaderboard bên ph?i canvas
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


    // V? r?n và th?c an trong khung
    food.Draw();
    snake.Draw();
    // V? tu?ng ch?n
    wall.Draw();




    // Hien thi do kho o goc ben phai
    diffText = "Difficulty: ";
    if (difficulty == 0.3f) diffText += "Easy";
    else if (difficulty == 0.2f) diffText += "Normal";
    else if (difficulty == 0.1f) diffText += "Hard";
    else diffText += "Custom";
    DrawText(diffText.c_str(), GetScreenWidth() - 200, 10, 20, LIGHTGRAY);


    // hi?n th? di?m s?
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
        // X? lý hu?ng di t? bàn phím
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


// Ki?m tra va ch?m v?i th?c an
void Game::CheckCollisionWithFood() {
    if (Vector2Equals(snake.body[0], food.position)) {
        food.position = food.GenerateRandomPos(snake.body, wall);
        snake.addSegment = true;


        score = score + 10;


        PlaySound(eatSound);
    }
}


// Ki?m tra va ch?m v?i biên
void Game::CheckCollisionWithEdges() {
    if (snake.body[0].x == cellCount || snake.body[0].x == -1 ||
        snake.body[0].y == cellCount || snake.body[0].y == -1) {
        GameOver();
    }
}


// Ki?m tra va ch?m v?i tu?ng
void Game::CheckCollisionWithWall() {
    if (wall.CollidesWith(snake.body[0])) {
        GameOver();
    }
}


// Ki?m tra va ch?m v?i duôi r?n
void Game::CheckCollisionWithTail() {
    std::deque<Vector2> headless = snake.body;
    headless.pop_front();
    if (ElementInDeque(snake.body[0], headless)) {
        GameOver();
    }
}


void Game::GameOver() {
    SaveScoreToFile();           // Luu di?m
    running = false;
    PlaySound(wallSound);


    // B? reset snake d? hi?n th? l?i khi choi l?i
    showPlayAgain = true;
    showGameOver = true;
}




void Game::SaveScoreToFile() {
    std::ofstream file("leaderboard.txt", std::ios::app);  // Ghi ti?p vào file
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


    // S?p x?p gi?m d?n theo di?m
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
    InitAudioDevice();  // Kh?i t?o h? th?ng âm thanh
    bgMusic = LoadMusicStream("assets/Sounds/background.mp3");
    PlayMusicStream(bgMusic);
    SetMusicVolume(bgMusic, 0.5f); // Gi?m âm lu?ng n?u c?n
    isMusicPlaying = true; // Reset tr?ng thái nh?c n?n
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


