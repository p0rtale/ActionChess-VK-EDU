#include "game.h"
#include "tile.h"
#include <iostream>

using namespace std;

int main()
{
    Game g;
    g.makeMove( 27, 8, 6);
    g.makeMove( 0, 1, 4);
    sleep(10);
    return 0;
}