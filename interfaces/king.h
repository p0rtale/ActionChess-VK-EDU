#ifndef KING_H
#define KING_H
#include "tile.h"
#include "figure.h"

class King :public Figure
{
public:
    King();
    ~King();
    bool isMoveCorrect();
};

#endif