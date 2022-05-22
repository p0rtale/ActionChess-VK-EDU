#pragma once
#include "BasicView.hpp"
#include "BasicModel.hpp"
#include <SFML/Graphics.hpp>

enum StageState{
    STAGE_ACTIVE,
    STAGE_FREEZE,
    STAGE_WAITING
};
 

class BasicController{
//Абстрактный класс для controller
public:
    virtual void init() = 0 ;    
    virtual void run() = 0 ;

    BasicController(BasicController const& other) = delete;
    BasicController &operator=(BasicController const& other) = delete;
    BasicController(BasicController&& that) = delete;
    BasicController &operator=(BasicController&& that) = delete;
    friend void swap(BasicController& lhs, BasicController& rhs) = delete;
    BasicController() = default;
    virtual ~BasicController() = default;
protected:
    StageState state;
    BasicView* view;
    BasicModel* model;
    sf::RenderWindow* window;
};