#ifndef QUEEN_H
#define QUEEN_H
#include "tile.h"
#include "figure.h"

class Queen :public Figure
{
public:
    Queen(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};

#endif