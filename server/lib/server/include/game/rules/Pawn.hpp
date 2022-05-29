#pragma once

#include "Figure.hpp"

class Pawn :public Figure
{
public:
    Pawn(int id, char color, int count);
    bool isMoveCorrect(Tile end_position, Field* f, Tile startPosition);
};
