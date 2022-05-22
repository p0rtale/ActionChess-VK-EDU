#pragma once
#include "BasicController.hpp"
#include <SFML/Graphics.hpp>
class MenuController: public BasicController{
public:
    void init() override;    
    void run() override;
    MenuController(BasicView* inp_view, BasicModel* inp_model, sf::RenderWindow* inp_window){
        view = inp_view;
        model = inp_model;
        window = inp_window;
        init();
    };

    ~MenuController() = default;
};