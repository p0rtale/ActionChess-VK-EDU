#ifndef KING_H
#define KING_H
#include "tile.h"
#include "figure.h"

class King :public Figure
{
public:
    King(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};

#endif