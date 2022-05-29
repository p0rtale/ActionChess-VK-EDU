#pragma once

class Field
{
private:
    bool map[8][8];
public:
    Field();
    bool isEnpty(int row, int column);
    void feelCell(int row, int column, bool b);
    //~Field();
};
