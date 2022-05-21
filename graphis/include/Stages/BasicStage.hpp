#pragma once 

#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "BasicView.hpp"
#include "BasicController.hpp"
#include "BasicModel.hpp"

class BasicStage{ 
/* Абстактный класс этапа (этап меню, этап комнаты и тд)
// содержит Controller, View и Model этапа
//
*/
public:
    virtual void init(sf::RenderWindow* inp_window);
    virtual BasicStage* run();
    BasicStage();
    virtual ~BasicStage() = default;
    BasicStage(BasicStage const& other) = delete;
    BasicStage &operator=(BasicStage const& other) = delete;
    BasicStage(BasicStage&& that) = delete;
    BasicStage &operator=(BasicStage&& that) = delete;
    friend void swap(BasicStage& lhs, BasicStage& rhs) = delete;
protected:
    sf::RenderWindow* window;
    std::string window_head_name = "Action Chess";
    BasicView* view;
    BasicController* controller;
    BasicModel* model;

    
};

