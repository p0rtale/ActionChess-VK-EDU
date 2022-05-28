#ifndef TILE_H
#define TILE_H
#include <iostream>
struct Tile
{
    int column;
    int row;
    Tile( int column, int row);
    Tile();
    bool isCorrect();
    void range(Tile t1, Tile t2);
    void print();
    bool isEqual(Tile tile);
};

#endif