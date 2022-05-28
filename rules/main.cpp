#include "game.h"
#include "tile.h"
#include <iostream>

using namespace std;

int main()
{
    Game g;
    g.makeMove('b', 27, 8, 6);
    sleep(10);
    return 0;
}