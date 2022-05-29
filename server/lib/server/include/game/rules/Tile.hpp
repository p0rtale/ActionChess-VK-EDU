#pragma once

#include <iostream>

struct Tile
{
    int column;
    int row;
    Tile( int row, int column);
    Tile();
    bool isCorrect();
    void range(Tile t1, Tile t2);
    void print();
    bool isEqual(Tile tile);
    void copy(Tile t1);
};
