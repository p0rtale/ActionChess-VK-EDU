#include "GroupFigure.h"

std::vector<Figure> GroupFigure::getFigures(){
    return Figures;
}

std::vector<sf::Sprite> GroupFigure::getSprites()
{
    std::vector<sf::Sprite> result;
    for (int i=0;i < Figures.size();++i){
        result.push_back(Figures[i].getSprite());
    }
    return result;
}