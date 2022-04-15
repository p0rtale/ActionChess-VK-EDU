#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
struct collider{
    int x;
    int y;
    int width;
    int height;
};
class Sprite
{
private:
    collider collide;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    sf::Sprite getSprite();
};