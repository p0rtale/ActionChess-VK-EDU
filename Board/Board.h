#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
//#include "Sprite.h"
struct collider{
    int x;
    int y;
    int width;
    int height;
};
class Board
{ 
    private:
    collider collide;
    sf::Sprite sprite;
    sf::Texture texture;
    public:
    sf::Sprite getSprite();
};
#endif