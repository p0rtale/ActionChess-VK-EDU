#include "figure.h"
#include "rock.h"
#include <math.h>
#include <iostream>

    Rock::Rock(int id, char color, int count)
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
    bool Rock::isMoveCorrect(Tile range)
    {
        range.column = abs(range.column);
        range.column = abs(range.column);
        Tile temp(range.row, range.column);
        if (range.column == 0 && range.row != 0)
        {
            // while (temp.row > 0)
            // {
            //     if ()
            // }
            return true;
        }
        else if (range.column != 0 && range.row == 0)
            return true;
        else
            return false;
    }