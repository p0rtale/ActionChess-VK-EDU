#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "BasicModel.hpp"
#include "BasicWidget.hpp"
#include <memory>
class BasicView{
//Абстрактный класс для view
public:
    virtual void init()=0;    
    virtual void render()=0;

    BasicView(BasicView const& other) = delete;
    BasicView &operator=(BasicView const& other) = delete;
    BasicView(BasicView&& that) = delete;
    BasicView &operator=(BasicView&& that) = delete;
    friend void swap(BasicView& lhs, BasicView& rhs) = delete;
    BasicView() = default;
    virtual ~BasicView() = default;
protected:
    sf::RenderWindow* window;
    BasicModel* model;
    
    sf::Texture background_image;
    sf::Sprite background;
    
    sf::Font font;
    sf::Vector2f size;
    bool visible;
    std::vector<std::shared_ptr<BasicWidget>> widgets;
    
};

