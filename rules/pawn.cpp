#include "figure.h"
#include "pawn.h"
#include <math.h>
#include <iostream>

    Pawn::Pawn(int id, char color, int count)
    {
        this->id = id;
        this->color = color;
        this->type = PAWN;
        // no magic numbers thats how chess works
        if (color == 'w')
            this->location = Tile(count, 2);
        else 
            this->location = Tile(count, 7);
    }
    bool Pawn::isMoveCorrect(Tile range)
    {
        if (this->color == 'b')
            range.column = -1 * (range.column);

                switch (range.column)
                {
                case 1:
                    if ((range.row == 1 || range.row == -1) && this->isAtack())
                        return true;
                    else if (range.row == 0) 
                        return true;
                    else
                        return false;
                    break;

                case 2:
                    if (range.row == 0)
                    {
                        if (this->color == 'b' && this->location.column == 7)
                            return true;
                        else if (this->location.column == 2)
                                return true;
                    }
                    break;
                    
                default:
                    return false;
                    break;
                }
        return false;
    }