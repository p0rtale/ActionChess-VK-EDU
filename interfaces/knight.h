#ifndef KNIGHT_H
#define KNIGHT_H
#include "tile.h"
#include "figure.h"

class Knight :public Figure
{
public:
    Knight();
    ~Knight();
    bool isMoveCorrect();
};

#endif