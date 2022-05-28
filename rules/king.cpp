#include "figure.h"
#include "king.h"
#include <math.h>
#include <iostream>

    King::King(int id, char color, int count)
    {
        this->id = id;
        this->color = color;
        this->type = KING;
        // no magic numbers thats how chess works
        if (color == 'w')
            this->location = Tile(count, 1);
        else 
            this->location = Tile(count, 8);
    }
    bool King::isMoveCorrect(Tile range, Field* f, Tile startPosition)
    {
        range.column = abs(range.column);
        range.row = abs(range.row);
        if (range.column == 1 || range.row == 1)
            return true;
        else
            return false;
    }