#pragma once
#include "BasicController.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BasicWidget.hpp"
#include "CursorController.hpp"
#include "MenuModel.hpp"
#include "MenuView.hpp"
#include <thread>
#define DEBUG
void throw_error(sf::String err);
class MenuController: public BasicController{
public:
    void init() override;    
    void run() override;
    MenuController(MenuView* inp_view, MenuModel* inp_model, sf::RenderWindow* inp_window){
        view = inp_view;
        model = inp_model;
        window = inp_window;
        init();
    };
    

    ~MenuController(){
        threads.clear();
    };
protected:
    MenuView* view; // TODO: Законно ли переропределять?
    MenuModel* model;   
    
    private:
        
        BasicWidget* widget_on_focus = NULL;
        std::vector<std::thread> threads;
private:
    void handle_name_enter();      
    
    sf::String err;

};

