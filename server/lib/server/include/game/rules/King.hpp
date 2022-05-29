#pragma once

#include "Tile.hpp"
#include "Figure.hpp"

class King :public Figure
{
public:
    King(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};
