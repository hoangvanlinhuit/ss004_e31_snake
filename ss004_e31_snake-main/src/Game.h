// Game.h
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
    void LoadLeaderboard(); // mới
    void ShowLeaderboard(); // giữ nếu cần
    bool showPlayAgain; // hiển thị nút sau khi thua


    Snake snake;
    Food food;
    bool running;
    int score;
    std::string playerName; // nhập từ người chơi

private:
    Sound eatSound;
    Sound wallSound;
    std::vector<Player> leaderboard; // mới
};

#endif