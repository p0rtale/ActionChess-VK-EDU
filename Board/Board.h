#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include "Sprite.h"

class Board : public Sprite
{   
private: 
    collider rect_collide;
    sf::Sprite rect_sprite;
    sf::Texture rect_texture;

public:
    Board();
    sf::Sprite get_rect();
    void update() override;
    
};
#endif