#ifndef PAWN_H
#define PAWN_H
#include "figure.h"

class Pawn :public Figure
{
public:
    Pawn(int id, char color, int count);
    bool isMoveCorrect(Tile end_position, Field* f, Tile startPosition);
};

#endif