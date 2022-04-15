#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figure.h"
class GroupFigure
{
    private:

    std::vector<Figure> Figures;

    int CountAlive;
    int CountDeath;



    public:
    GroupFigure();
    void addFigure();
    bool delFigure();
    void update(float dtAsSeconds);
    std::vector<sf::Sprite> getSprites();
};