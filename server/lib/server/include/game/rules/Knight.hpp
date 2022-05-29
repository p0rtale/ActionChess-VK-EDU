#pragma once

#include "Tile.hpp"
#include "Figure.hpp"

class Knight :public Figure
{
public:
    Knight(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};
