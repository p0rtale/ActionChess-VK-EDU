#include "Knight.hpp"

#include <math.h>
#include <iostream>

#include "Figure.hpp"

    Knight::Knight(int id, char color, int count)
    {
        this->id = id;
        this->color = color;
        this->type = KNIGHT;
        // no magic numbers thats how chess works
        if (color == 'w')
            this->location = Tile(count, 1);
        else 
            this->location = Tile(count, 8);
    }
    bool Knight::isMoveCorrect(Tile range, Field* f, Tile startPosition)
    {
        range.row = abs(range.row);
        range.column = abs(range.column);

        if (range.column == 2 && range.row == 1)
            return true;
        else if (range.column == 1 && range.row == 2)
            return true;
        else
            return false;
    }