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
    bool Rock::isMoveCorrect(Tile range, Field* f, Tile startPosition)
    {
        int i, max_path;
        if (range.column == 0 && range.row != 0)
        {
            max_path = range.row;
            if (max_path <= 0 )
                i = -1;
            else
                i = 1;
            max_path = abs(max_path) - 1;

                while (max_path > 0)
                {
                        if (!f->isEnpty(startPosition.row + (i * max_path), startPosition.column))
                            {
                                std::cout<<"Error there is another figure on your way "<<startPosition.row + (i * max_path)<<" "<< startPosition.column<<std::endl;
                                return false;
                            }
                    max_path--;
                }
            return true;
        }
        else if (range.column != 0 && range.row == 0)
        {
            max_path = range.column;
            if (max_path <= 0 )
                i = -1;
            else
                i = 1;
            max_path = abs(max_path) - 1;

                while (max_path > 0)
                {
                        if (!f->isEnpty(startPosition.row , startPosition.column + (i * max_path)))
                            {
                                std::cout<<"Error there is another figure on your way "<<startPosition.row <<" "<< startPosition.column + (i * max_path)<<std::endl;
                                return false;
                            }
                    max_path--;
                }
            return true;
        }
        else
            return false;
    }