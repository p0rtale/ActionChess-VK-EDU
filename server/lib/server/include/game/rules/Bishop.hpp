#pragma once

#include "Tile.hpp"
#include "Figure.hpp"

class Bishop :public Figure
{
public:
    Bishop(int id, char color, int count);
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
};
