#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct collider{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};
struct Tile {
    unsigned int row = 0;
    unsigned int column = 0;
};
class Sprite
{
protected:
    Tile position;
    collider collide;
    sf::Sprite sprite;
    sf::Texture texture;
    unsigned int ID;
    std::string type;
    char color;
public:
    Sprite();
    Sprite(Tile position_,collider collide_,std::string img,unsigned int ID_,std::string type_,char color_);
    sf::Sprite getSprite();
    Tile wait_pressing(sf::Event event,sf::RenderWindow window);
    int getID();
};