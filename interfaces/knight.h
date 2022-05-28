#ifndef KNIGHT_H
#define KNIGHT_H
#include "tile.h"
#include "figure.h"

class Knight :public Figure
{
public:
    Knight(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};

#endif