#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

struct ScoreEntry {
    std::string name;
    int score;
};

class Leaderboard {
public:
    Leaderboard(const std::string& filename);
    void Load();
    void Save();
    void AddScore(const std::string& name, int score);
    void Draw(int x, int y);
private:
    std::string filename;
    std::vector<ScoreEntry> entries;
};

#endif
