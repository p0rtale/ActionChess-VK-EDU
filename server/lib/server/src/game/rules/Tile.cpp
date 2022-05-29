#include "Tile.hpp"

    int column;
    int row;
    Tile::Tile(int row, int column)
    {
        this->column = column;
        this->row = row;
    }
    Tile::Tile()
    {
        this->column = 0;
        this->row = 0;
    }
    bool Tile::isCorrect()
    {
        if (this->column < 1 || this->column > 8)
            return false;
        if (this->row < 1 || this->row > 8)
            return false;
        return true;
    }
    void Tile::range(Tile t1, Tile t2)
    {
        this->column =  t2.column - t1.column;
        this->row = t2.row - t1.row;
    }
    void Tile::print()
    {
        std::cout<<(char)('a' + this->row - 1)<<this->column<<std::endl;
    }
    bool Tile::isEqual(Tile tile)
    {
        if (this->column == tile.column && this->row == tile.row)
            return true;
        else
            return false;
    }
    void Tile::copy(Tile t1)
    {
        this->column = t1.column;
        this->row = t1.row;
    }
