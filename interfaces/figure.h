#ifndef FIGURE_H
#define FIGURE_H
#include "tile.h"

class Figure
{
protected:
    int id;
    Tile location;
    bool isDead;
    bool isOnCallDown;
    bool isInFlight;
public:
    Figure(/* args */);
    ~Figure();
    bool isDead();
    bool isOnCallDown();
    bool isInFlight();
};

#endif