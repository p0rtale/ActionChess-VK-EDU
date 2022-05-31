#include <SFML/Graphics.hpp>
#include "RoomStage.hpp"
#include "Assets.hpp"
#include "BasicStage.hpp"
#include "RoomModel.hpp"
#include "RoomController.hpp"
#include "RoomView.hpp"
#include "Client.hpp"
#include "MenuModel.hpp"
void RoomStage::init(){
    
    
}

RoomStage::RoomStage(sf::RenderWindow* inp_window, Client* inp_c,User player, std::vector<User> users, Rooms room){
    c = inp_c;
    window = inp_window;
    model = new RoomModel(c);
    view = new RoomView(window,model);
    controller = new RoomController(view,model,window);
    model->set_init(player,room,users);
}
RoomStage::~RoomStage(){
    delete model;
    delete view;
    delete controller;
    
}
BasicStage* RoomStage::run(){
    while(window->isOpen() and nado){
        nado = controller->run() && window->isOpen();
    }
    if (window->isOpen()){
        if(!nado){
            // if(controller->state == STAGE_JOINED_ROOM){
                
            // }
        }
    }
    return this;
}

