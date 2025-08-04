#include "Leaderboard.h"
#include <iostream>
#include <raylib.h>

Leaderboard::Leaderboard(const std::string& filename) : filename(filename) {}

void Leaderboard::Load() {
    entries.clear();
    std::ifstream file(filename);
    std::string name;
    int score;
    while (file >> name >> score) {
        entries.push_back({name, score});
    }
    file.close();
}

void Leaderboard::Save() {
    std::ofstream file(filename);
    for (const auto& entry : entries) {
        file << entry.name << " " << entry.score << "\n";
    }
    file.close();
}

void Leaderboard::AddScore(const std::string& name, int score) {
    entries.push_back({name, score});
    std::sort(entries.begin(), entries.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });
    if (entries.size() > 5) entries.resize(5);
    Save();
}

void Leaderboard::Draw(int x, int y) {
    DrawText("Leaderboard", x, y, 20, DARKGRAY);
    for (size_t i = 0; i < entries.size(); ++i) {
        std::string line = entries[i].name + ": " + std::to_string(entries[i].score);
        DrawText(line.c_str(), x, y + 30 + i * 25, 20, DARKGRAY);
    }
}
