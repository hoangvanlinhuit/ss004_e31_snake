#ifndef LEADERBOARD_H
#define LEADERBOARD_H

// Thu vien chua cac kieu du lieu co ban
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

// Cau truc luu thong tin diem so cua nguoi choi
struct ScoreEntry {
    std::string name;   // Ten nguoi choi
    int score;          // Diem so dat duoc
};

// Lop quan ly bang xep hang
class Leaderboard {
public:
    // Ham tao, nhan ten file de luu va doc diem so
    Leaderboard(const std::string& filename);

    // Doc diem so tu file vao entries
    void Load();

    // Ghi diem so trong entries vao file
    void Save();

    // Them diem moi vao bang xep hang
    void AddScore(const std::string& name, int score);

    // Ve bang xep hang tai vi tri x, y tren man hinh
    void Draw(int x, int y);

private:
    std::string filename;            // Ten file luu tru bang diem
    std::vector<ScoreEntry> entries; // Danh sach diem so
};

#endif
