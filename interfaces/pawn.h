#ifndef PAWN_H
#define PAWN_H
#include "figure.h"

class Pawn :public Figure
{
public:
    Pawn();
    ~Pawn();
    bool isMoveCorrect();
};

#endif