#pragma once

#include "Tile.hpp"
#include "Figure.hpp"

class Queen :public Figure
{
public:
    Queen(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};
