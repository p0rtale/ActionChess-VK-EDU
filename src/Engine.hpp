#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GroupFigure.hpp"
#include "BoardTable.hpp"
 
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
    std::shared_ptr<BoardTable> board;

    std::shared_ptr<GroupFigure> player_figures;

    std::shared_ptr<GroupFigure> opponent_figures;

private:

    void update(sf::Event event);

    void draw();
 
public:

    // Конструктор движка
    Engine();

    ~Engine();
 
    // Функция старт вызовет все приватные функции
    void start();
 
};