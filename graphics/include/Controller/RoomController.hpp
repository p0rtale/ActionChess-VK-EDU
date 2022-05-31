#pragma once
#include "BasicController.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BasicWidget.hpp"
#include "CursorController.hpp"
#include "RoomModel.hpp"
#include "RoomView.hpp"
#include <thread>
#include <MenuController.hpp>

#define UPDATE_INTERVAL_TIME 1
enum RoomState{
    // STAGE_ASK_NAME,
    // STAGE_WAIT_NAME_CONFIRMATION,
    // STAGE_CHOOSE_ROOM,
    // STAGE_WAIT_ROOM_CONFIRMATION,
};

class RoomController: public BasicController{
public:
    void init() override;    
    bool run() override;
    RoomController(RoomView* inp_view, RoomModel* inp_model, sf::RenderWindow* inp_window){
        view = inp_view;
        model = inp_model;
        window = inp_window;
        init();
    };
    

    ~RoomController(){

    };
protected:
    RoomView* view; // TODO: Законно ли переропределять?
    RoomModel* model;   
    
    private:
        
        BasicWidget* widget_on_focus = NULL;
private:
    MenuState   state;
    void handle_ready();
    void handle_msg_send();      
    void ask_for_ready();
    sf::String err;
    sf::Clock update_timer;
};

