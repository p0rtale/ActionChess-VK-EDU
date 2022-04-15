#ifndef ROCK_H
#define ROCK_H
#include "tile.h"
#include "figure.h"

class Rock :public Figure
{
public:
    Rock();
    ~Rock();
    bool isMoveCorrect();
};

#endif