// utils.cpp - Chua cac ham tien ich dung trong game

#include "utils.h"
#include <raylib.h>
#include <raymath.h>

// Bien toan cuc dieu khien viec cho phep di chuyen
bool allowMove = false;

// Khởi tạo màu sắc sử dụng trong game
Color green      = { 0, 228, 48, 255 };   // xanh lá tươi
Color darkGreen  = { 0, 117, 44, 255 };   // xanh lá đậm
Color blue       = { 0, 121, 241, 255 };  // xanh dương sáng
Color darkBlue   = { 0, 82, 172, 255 };   // xanh dương đậm
Color red        = { 230, 41, 55, 255 };  // đỏ tươi
Color darkRed    = { 160, 20, 30, 255 };  // đỏ đậm
Color yellow     = { 253, 249, 0, 255 };  // vàng
Color gray       = GRAY;                 // xám mặc định của raylib
Color lightGray  = LIGHTGRAY;            // xám nhạt mặc định
Color orange     = { 255, 161, 0, 255 };  // cam

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
