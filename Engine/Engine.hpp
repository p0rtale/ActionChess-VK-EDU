#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GroupFigure.h";
#include "Board.h";
 
 
class Engine
{
private:
 
    sf::RenderWindow window;  
 
    // Create Sprite and Tecture
    sf::Sprite BackgroundSprite;
    sf::Texture BackgroundTexture;
    sf::Font font;
    
    int Round;
 
    // Create object of class Game
    GroupFigure figures;
    Board board;
 
    void update(float dtAsSeconds);
    void draw();
    
public:
    // Конструктор движка
    Engine();
 
    // Функция старт вызовет все приватные функции
    void start();

    void changefont();
 
};