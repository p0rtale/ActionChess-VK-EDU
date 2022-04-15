#ifndef BISHOP_H
#define BISHOP_H
#include "tile.h"
#include "figure.h"

class Bishop :public Figure
{
public:
    Bishop();
    ~Bishop();
    bool isMoveCorrect();
};

#endif