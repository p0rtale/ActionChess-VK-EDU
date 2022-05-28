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
        range.column = abs(range.column);
        range.column = abs(range.column);
        int i;

        if (range.column == 0 && range.row != 0)
        {
            i = range.row - 1;
                while (i > 0)
                {
                    if (this->color == 'w')
                    {
                        if (!f->isEnpty(startPosition.row + i, startPosition.column))
                            {
                                std::cout<<"Error there is another figure on your way "<<startPosition.row + i<<" "<< startPosition.column<<std::endl;
                                return false;
                            }
                    }
                    else
                    {
                        if (!f->isEnpty(startPosition.row - i, startPosition.column))
                            {
                                std::cout<<"Error there is another figure on your way "<<startPosition.row - i<<" "<< startPosition.column<<std::endl;
                                return false;
                            }
                    }
                    i--;
                }
            return true;
        }
        else if (range.column != 0 && range.row == 0)
        {
            i = range.column - 1;
            while (i > 0)
            {
                    if (this->color == 'w')
                    {
                        if (!f->isEnpty(startPosition.row , startPosition.column + i))
                            {
                                std::cout<<"Error there is another figure on your way "<<startPosition.row<<" "<< startPosition.column + i<<std::endl;
                                return false;
                            }
                    }
                    else
                    {
                        if (!f->isEnpty(startPosition.row , startPosition.column - i))
                            {
                                std::cout<<"Error there is another figure on your way "<<startPosition.row <<" "<< startPosition.column - i<<std::endl;
                                return false;
                            }
                    }
                i--;
            }
            
            return true;
        }
        else
            return false;
    }