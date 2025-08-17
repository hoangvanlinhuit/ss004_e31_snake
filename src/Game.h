#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
#include <raylib.h>
#include <string>
#include <vector>

struct LeaderboardEntry {
    std::string name;
    int score;
};

class Game {
public:
    Game();
    ~Game();

    void Draw();
    void Update();
    void GameOver();
    void Reset();

    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithTail();

    void SaveScoreToFile();
    void LoadLeaderboard();

    bool showGameOver = false; // Thêm biến này

private:
    Snake snake;
    Food food;
    bool running;
    int score;

    std::string playerName;
    std::vector<LeaderboardEntry> leaderboard;

    Sound eatSound;
    Sound wallSound;
};

#endif
