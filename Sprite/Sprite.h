#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
struct collider{
    int x;
    int y;
    int width;
    int height;
};
struct Tile {
    unsigned int column;
    unsigned int row;
};
class Sprite
{
protected:
    Tile position;
    collider collide;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    virtual sf::Sprite getSprite();
    virtual void update();
};