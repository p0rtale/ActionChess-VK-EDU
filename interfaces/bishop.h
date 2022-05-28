#ifndef BISHOP_H
#define BISHOP_H
#include "tile.h"
#include "figure.h"

class Bishop :public Figure
{
public:
    Bishop(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};

#endif