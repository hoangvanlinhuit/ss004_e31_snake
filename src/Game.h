#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
#include <string>
#include <vector>

struct Player {
    std::string name;
    int score;
};

class Game {
public:
    Game();
    ~Game();

    void Draw();
    void Update();
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithTail();
    void GameOver();
    void SaveScoreToFile();
    void LoadLeaderboard();
    void ShowLeaderboard();

    //  
    Snake snake;
    Food food;
    bool running;
    int score;
    std::string playerName;
    bool showPlayAgain;
    float difficulty; // 0.3 = Easy, 0.2 = Normal, 0.1 = Hard

    // Dùng cho màn hình Game Over
    bool showGameOver;
    Rectangle playAgainButton;
    void Reset();

private:
    Sound eatSound;
    Sound wallSound;
    std::vector<Player> leaderboard;

    // Các hàm phụ trợ
    
    void CheckMouseEvents();
    void DrawGameOverScreen();
    void DrawPlayAgainButton();
};

#endif
