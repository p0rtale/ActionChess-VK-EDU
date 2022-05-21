#include <SFML/Graphics.hpp>
#include "MenuStage.hpp"
#include "Assets.hpp"
#include "BasicStage.hpp"
#include "MenuModel.hpp"
#include "MenuController.hpp"
#include "MenuView.hpp"

void MenuStage::init(sf::RenderWindow* inp_window){
    window = inp_window;
    model = new MenuModel();
    view = new MenuView(window,model);
    controller = new MenuController(view,model);
    
}
MenuStage::~MenuStage(){
    delete model;
    delete view;
    delete controller;
    
}
BasicStage* MenuStage::run(){
    while(window->isOpen()){
    controller->run();
    }
}

