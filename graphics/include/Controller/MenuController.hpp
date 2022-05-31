#pragma once
#include "BasicController.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BasicWidget.hpp"
#include "CursorController.hpp"
#include "MenuModel.hpp"
#include "MenuView.hpp"
#include <thread>

#define UPDATE_INTERVAL_TIME 1
enum MenuState{
    STAGE_JOINED_ROOM,
    STAGE_ASK_NAME,
    STAGE_WAIT_NAME_CONFIRMATION,
    STAGE_CHOOSE_ROOM,
    STAGE_WAIT_ROOM_CONFIRMATION,
};
 
void throw_error(sf::String err);

class MenuController: public BasicController{
public:
    void init() override;    
    bool run() override;
    MenuController(MenuView* inp_view, MenuModel* inp_model, sf::RenderWindow* inp_window){
        view = inp_view;
        model = inp_model;
        window = inp_window;
        init();
    };
    

    ~MenuController(){

    };
        MenuState   state;

protected:
    MenuView* view; // TODO: Законно ли переропределять?
    MenuModel* model;   
    
    private:
        
        BasicWidget* widget_on_focus = NULL;
private:
    void handle_create_room();
    void handle_join_room();

    void handle_name_enter();      
    void ask_for_rooms();
    
    sf::String err;
    sf::Clock update_timer;
};

