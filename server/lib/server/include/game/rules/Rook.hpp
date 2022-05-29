#pragma once

#include "Tile.hpp"
#include "Figure.hpp"

class Rook :public Figure
{
public:
    Rook(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};
