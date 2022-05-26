#pragma once

#include <SFML/Graphics.hpp>
#include "BasicView.hpp"

class MenuView:  public BasicView{
public:
    void init() override;    
    void render() override;
    ~MenuView() override;
    MenuView(sf::RenderWindow* inp_window, BasicModel* inp_model){
        window = inp_window;
        model = inp_model;
        init();
    };
private:
    menu_assets menu_media;
    general_assets general_media;
};
