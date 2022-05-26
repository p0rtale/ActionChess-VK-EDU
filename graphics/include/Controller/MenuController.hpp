#pragma once
#include "BasicController.hpp"
#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "CursorController.hpp"
#define DEBUG

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
    private:
        
        BasicWidget* widget_on_focus = NULL;
};