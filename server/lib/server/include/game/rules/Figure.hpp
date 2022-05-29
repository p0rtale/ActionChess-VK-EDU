#pragma once

#include "Tile.hpp"
#include "Field.hpp"

#define PAWN 'p'
#define ROOK 'r'
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
    bool atack;
public:
    Figure();
    bool isDead();
    bool isOnCallDown();
    bool isInFlight();
    bool isMoveCorrect(Tile range, Field* f, Tile startPosition);
    int getId();
    char getType();
    void setPosition(Tile new_position);
    Tile getPosition();
    void die();
    void setOnCallDown();
    void endCallDown();
    void setInFlight();
    void endFlight();
    char getColor();
    void kill(Figure figure);
    bool isAtack();
    void setAtack(bool b);
};
