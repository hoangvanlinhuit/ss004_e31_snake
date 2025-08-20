#include "Leaderboard.h"
#include <iostream>
#include <raylib.h>

// Ham khoi tao, gan ten file luu bang xep hang
Leaderboard::Leaderboard(const std::string& filename) : filename(filename) {}

// Doc diem tu file va nap vao danh sach entries
void Leaderboard::Load() {
    entries.clear(); // Xoa du lieu cu
    std::ifstream file(filename);
    std::string name;
    int score;
    // Doc tung dong gom ten va diem
    while (file >> name >> score) {
        entries.push_back({name, score});
    }
    file.close();
}

// Ghi danh sach entries vao file
void Leaderboard::Save() {
    std::ofstream file(filename);
    for (const auto& entry : entries) {
        file << entry.name << " " << entry.score << "\n";
    }
    file.close();
}

// Them diem moi vao bang xep hang, sap xep giam dan va chi giu 5 diem cao nhat
void Leaderboard::AddScore(const std::string& name, int score) {
    entries.push_back({name, score});
    // Sap xep entries theo diem giam dan
    std::sort(entries.begin(), entries.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });
    // Chi giu 5 diem cao nhat
    if (entries.size() > 5) entries.resize(5);
    Save(); // Luu lai vao file
}

// Ve bang xep hang len man hinh tai vi tri x, y
void Leaderboard::Draw(int x, int y) {
    DrawText("Leaderboard", x, y, 20, DARKGRAY);
    for (size_t i = 0; i < entries.size(); ++i) {
        std::string line = entries[i].name + ": " + std::to_string(entries[i].score);
        DrawText(line.c_str(), x, y + 30 + i * 25, 20, DARKGRAY);
    }
}
