// utils.h
#ifndef UTILS_H
#define UTILS_H
#include <raylib.h>
#include <deque>

extern bool allowMove;
extern Color green;
extern Color darkGreen;
extern Color blue;
extern Color darkBlue;
extern Color red;
extern Color darkRed;
extern int cellSize;
extern int cellCount;
extern int offset;

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque);
bool EventTriggered(double interval);

#endif

