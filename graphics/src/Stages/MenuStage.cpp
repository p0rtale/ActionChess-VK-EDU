#include <SFML/Graphics.hpp>
#include "MenuStage.hpp"
#include "Assets.hpp"
#include "BasicStage.hpp"
#include "MenuModel.hpp"
#include "MenuController.hpp"
#include "MenuView.hpp"
#include "Client.hpp"
#include "RoomStage.hpp"
void MenuStage::init(){
    model = new MenuModel(c);
    view = new MenuView(window,model);
    controller = new MenuController(view,model,window);
    
}

MenuStage::MenuStage(sf::RenderWindow* inp_window, Client* inp_c){
    c = inp_c;
    window = inp_window;
    init();
}
MenuStage::~MenuStage(){
    delete model;
    delete view;
    delete controller;
    
}
BasicStage* MenuStage::run(){
    while(window->isOpen() and nado){
        nado = controller->run() && window->isOpen();
    }
    if (window->isOpen()){
        if(!nado){
            if(controller->state == STAGE_JOINED_ROOM){
                RoomStage* room = new RoomStage(window,c,model->player,model->jUsers,model->jroom);
                return room;
            

            }
        }
    }
    return this;
}

