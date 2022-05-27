#ifndef TILE_H
#define TILE_H

struct Tile
{
    int column;
    int row;
    Tile( int column, int row);
    Tile();
    bool isCorrect();
    void range(Tile t1, Tile t2);
};

#endif