#ifndef FIGURE_H
#define FIGURE_H
#include "tile.h"

#define PAWN 'p'
#define ROCK 'r'
#define KING 'k'
#define QUEEN 'q'
#define BISHOP 'b'
#define KNIGHT 'h'

class Figure
{
protected:
    int id;
    char color;
    Tile location;
    bool dead;
    bool onCallDown;
    bool inFlight;
    char type;
public:
    Figure();
    bool isDead();
    bool isOnCallDown();
    bool isInFlight();
    bool isMoveCorrect(Tile end_position);
    int getId();
    char getType();
    void setPosition(Tile new_position);
    Tile getPosition();
};

#endif