#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Sprite.hpp"
class BoardTable
{
    private:
    std::vector<Sprite> Figures;
    collider collide_board;
    std::vector<collider> vec_collide(sf::Vector2i resolution);
    public:
    BoardTable(sf::Vector2i resolution);

    std::vector<sf::Sprite> getSprites();
    
    Tile touch_board(sf::Event event,sf::RenderWindow& window);
};