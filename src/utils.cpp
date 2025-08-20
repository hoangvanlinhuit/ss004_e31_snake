// utils.cpp - Chua cac ham tien ich dung trong game

#include "utils.h"
#include <raylib.h>
#include <raymath.h>

// Bien toan cuc dieu khien viec cho phep di chuyen
bool allowMove = false;

// Dinh nghia cac mau sac dung trong game
Color green = {173, 204, 96, 255};       // Mau xanh la
Color darkGreen = {43, 51, 24, 255};     // Mau xanh dam
Color blue = {72, 116, 191, 255};        // Mau xanh da troi
Color red = {255, 0, 0, 255};            // Mau do
Color darkBlue = {11, 83, 148, 255};     // Mau xanh bien dam
Color darkRed = {200, 0, 0, 255};        // Mau do dam

// Kich thuoc 1 o vuong trong ban do (don vi pixel)
int cellSize = 30;
// So luong o tren moi chieu cua ban do
int cellCount = 25;
// Khoang cach le tu canh cua cua so den ban do
int offset = 75;

// Thoi gian cap nhat cuoi cung
double lastUpdateTime = 0;

// Kiem tra xem mot Vector2 co nam trong deque hay khong
bool ElementInDeque(Vector2 element, std::deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (Vector2Equals(deque[i], element)) {
            return true; // Neu tim thay phan tu trong deque
        }
    }
    return false; // Khong tim thay
}

// Kiem tra xem da den thoi diem cap nhat moi chua
bool EventTriggered(double interval) {
    double currentTime = GetTime(); // Lay thoi gian hien tai
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true; // Cho phep cap nhat
    }
    return false; // Chua den thoi diem cap nhat
}
