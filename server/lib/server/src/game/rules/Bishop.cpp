#include "Bishop.hpp"

#include <math.h>
#include <iostream>

#include "Figure.hpp"


    Bishop::Bishop(int id, char color, int count)
    {
        this->id = id;
        this->color = color;
        this->type = BISHOP;
        // no magic numbers thats how chess works
        if (color == 'w')
            this->location = Tile(count, 1);
        else 
            this->location = Tile(count, 8);
    }
    bool Bishop::isMoveCorrect(Tile range, Field* f, Tile startPosition)
    {
        int x, y, max_path;
        if (range.row >= 0)
            x = 1;
        else
            x = -1;
        if (range.column >= 0)
            y = 1;
        else
            y = -1;
        max_path = abs(range.row) - 1;
        if (abs(range.column) ==  abs(range.row))
        {

                while (max_path > 0)
                {
                        if (!f->isEnpty(startPosition.row + (x * max_path), startPosition.column + (y * max_path)))
                            {
                                std::cout<<"Error there is another figure on your way "<<startPosition.row + (x * max_path)<<" "<< startPosition.column + (y * max_path)<<std::endl;
                                return false;
                            }
                    max_path--;
                }
            return true;
        }
        else
            return false;
    }