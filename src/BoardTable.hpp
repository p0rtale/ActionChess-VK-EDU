#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Sprite.hpp"
class BoardTable
{
    private:

    std::vector<std::unique_ptr<Sprite>> Figures;

    collider collide_board;

    std::vector<collider> vec_collide(sf::Vector2i resolution);

    std::vector<Tile> vec_Tile();

    public:
    
    BoardTable(sf::Vector2i resolution);
    
    Tile touch_board(sf::Event event,sf::RenderWindow* window);

    void draw(sf::RenderWindow* window);
};