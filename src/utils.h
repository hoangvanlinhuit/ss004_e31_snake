// utils.h - Dinh nghia cac ham ho tro va bien toan cuc dung trong game

#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>
#include <deque>

// Bien toan cuc de kiem soat viec di chuyen cua ran
extern bool allowMove;

// Dinh nghia cac mau sac duoc su dung trong game
extern Color green;       // Mau xanh la
extern Color darkGreen;   // Mau xanh la dam
extern Color blue;        // Mau xanh da troi
extern Color darkBlue;    // Mau xanh dam
extern Color red;         // Mau do
extern Color darkRed;     // Mau do dam

// Cac thong so ve kich thuoc ban do
extern int cellSize;      // Kich thuoc moi o vuong
extern int cellCount;     // So o tren mot chieu cua ban do
extern int offset;        // Le giua ban do va vien cua so

// Kiem tra xem mot Vector2 co ton tai trong deque hay khong
bool ElementInDeque(Vector2 element, std::deque<Vector2> deque);

// Kiem tra xem da den thoi diem cap nhat moi chua (dua tren khoang thoi gian cho truoc)
bool EventTriggered(double interval);

#endif
