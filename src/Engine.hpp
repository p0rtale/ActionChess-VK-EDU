#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GroupFigure.hpp";
#include "BoardTable.hpp";
 
class Engine
{
private:
 
    sf::RenderWindow window;  
    sf::Vector2i resolution;
    // Создаем спрайт и текстуру
    sf::Sprite m_BackgroundSprite;
    sf::Texture m_BackgroundTexture;
    
    int Round;
 
    // Создаем экземпляры классов
    BoardTable* board;
    GroupFigure* player_figures;
    GroupFigure* opponent_figures;
   
 
    void update(float dtAsSeconds,sf::Event event);
    void draw();
 
public:
    // Конструктор движка
    Engine() = default;

    ~Engine() = default;
 
    // Функция старт вызовет все приватные функции
    void start();
 
};