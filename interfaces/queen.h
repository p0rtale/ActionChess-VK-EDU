#ifndef QUEEN_H
#define QUEEN_H
#include "tile.h"
#include "figure.h"

class Queen :public Figure
{
public:
    Queen();
    ~Queen();
    bool isMoveCorrect();
};

#endif