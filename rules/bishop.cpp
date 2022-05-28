#include "figure.h"
#include "bishop.h"
#include <math.h>
#include <iostream>

    Bishop::Bishop(int id, char color, int count)
    {
        this->id = id;
        this->color = color;
        this->type = ROCK;
        // no magic numbers thats how chess works
        if (color == 'w')
            this->location = Tile(count, 1);
        else 
            this->location = Tile(count, 8);
    }
    bool Bishop::isMoveCorrect(Tile range, Field* f, Tile startPosition)
    {
        range.column = abs(range.column);
        range.column = abs(range.column);
            return false;
    }