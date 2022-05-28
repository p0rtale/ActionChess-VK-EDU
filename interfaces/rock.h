#ifndef ROCK_H
#define ROCK_H
#include "tile.h"
#include "figure.h"

class Rock :public Figure
{
public:
    Rock(int id, char color, int count);
    bool isMoveCorrect(Tile range);
};

#endif