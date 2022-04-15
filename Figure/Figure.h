#pragma once
#include <SFML/Graphics.hpp>
//#include "Sprite.h"
struct collider{
    int x;
    int y;
    int width;
    int height;
};
class Figure{
private:
    int ID;
    sf::Vector2f position;
    sf::Sprite sprite;
    collider collide;
    sf::Texture texture;
    char color;
    bool Alive;
    bool isInFlight;
public:
    void update();
    int del();
    bool isInFlight();
    int getID();
    sf::Sprite getSprite();
};