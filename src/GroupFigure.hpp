#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figure.hpp"
#include "BoardTable.hpp"

class GroupFigure
{
    private:

        std::vector<Figure> Figures;

        int CountAlive = 16;
        int CountDeath = 0;
        bool player;
        bool isSelect;
        char color;
        std::vector<collider> vec_collide(sf::Vector2i resolution,bool player);
    public:
        GroupFigure(sf::Vector2i resolution,bool player_,char color);
        
        bool delFigure();

        void update(sf::Event event,sf::RenderWindow& window,BoardTable& board);
        
        std::vector<sf::Sprite> getSprites();
};