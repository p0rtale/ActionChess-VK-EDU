#include "field.h"

Field:: Field()
{
    for (int i = 2; i < 6; i++) // i for x, k for y
    {
        for (int k = 0; k < 8; k++)
            map[k][i] = true;
    }
    for (int i = 0; i < 2; i++) // feel white side
    {
        for (int k = 0; k < 8; k++)
            map[k][i] = false;
    }
    for (int i = 6; i < 8; i++) // feel black side
    {
        for (int k = 0; k < 8; k++)
            map[k][i] = false;
    }

}
void Field::feelCell(int row, int column, bool b)
{
    map[row - 1][column - 1] = b;
}
bool Field::isEnpty(int row, int column)
{
    return map[row-1][column-1];
}