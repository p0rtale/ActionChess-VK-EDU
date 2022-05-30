#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figure.hpp"

class GroupFigure
{
    private:

        std::vector<std::unique_ptr<Figure>> Figures;

        int CountAlive = 16;

        int CountDeath = 0;

        bool player;

        bool isSelect;

        char color;

        std::vector<collider> vec_collide(sf::Vector2i resolution,bool player);

    public:
    
        GroupFigure(sf::Vector2i resolution,bool player_,char color);
        
        void delFigure(int id);

        void update(sf::Event event,sf::RenderWindow* window,std::shared_ptr<BoardTable> board);

        void draw(sf::RenderWindow* window);
};