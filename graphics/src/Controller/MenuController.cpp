#include "BasicController.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>
#include "CursorController.hpp"
#include <functional>
#include <iostream>
#include <thread>
#include "Assets.hpp"
#include "Variables.hpp"
void MenuController::init(){
    state = STAGE_ASK_NAME;
    view->activate_name_request();
    std::function <void ()> handler = std::bind(&MenuController::handle_name_enter,this);
    view->set_name_button_handler(handler);
    handler = std::bind(&MenuController::handle_create_room,this);
    view->set_create_room_handler(handler);
    handler = std::bind(&MenuView::set_rooms_table_from_model ,view);
    model->set_room_update_handler(handler);
}    


void throw_error_maslo(sf::String err){
    
    sf::Font font;
    font.loadFromFile(GENERAL_FONT_GOST_PATH);
    sf::Text caption(err,font);
    caption.setFillColor(sf::Color(255,20,20));
    caption.setPosition(20.f,20.f);
    caption.setStyle(sf::Text::Style::Bold);
    sf::RenderWindow error_window(sf::VideoMode(300+caption.getGlobalBounds().width,100+caption.getGlobalBounds().height), "ERROR");

    sf::Event e;
    while (error_window.isOpen()){
        while (error_window.pollEvent(e)){
            if (e.type == sf::Event::Closed){
                    error_window.close();
                }
        }
        error_window.clear(sf::Color(212,208,200));
        error_window.draw(caption);

        error_window.display();

    }
    

}


void MenuController::handle_name_enter(){
    sf::String player_name = view->get_name();
    if (player_name.getSize() == 0){ //TODO: реализовать
        err =L"Пустое имя";
        std::thread t(throw_error_maslo,err);
        t.detach();
    }
    else{
        model->set_player(player_name);
        view ->activate_rooms();
        state = STAGE_CHOOSE_ROOM;

    }    
}

void MenuController::handle_create_room(){
    sf::String room_name = view->get_room_name();
    if (room_name.getSize() == 0){ //TODO: реализовать
        err =L"Пустое имя комнаты";
        //state = STAGE_FREEZE;
        std::thread t(throw_error_maslo,err);
        t.detach();
    }
    else{
        model->create_room(room_name.toAnsiString());
        view->disactivate_rooms();
    }   
}
void MenuController::run(){
    CursorController::get_instance().reset_cursor();
    sf::Event e;
        while (window->pollEvent(e))
        {            
            if((state == STAGE_ASK_NAME)||(state == STAGE_CHOOSE_ROOM)){
                switch (e.type)
                {
                    
                    case sf::Event::MouseMoved:
                    {
                        for(auto& widget:view->get_widget_vec()){
                            widget->on_mouse_over(window);
                        }
                        break;
                    }
                    case sf::Event::MouseButtonPressed:
                    {
                        for(auto& widget:view->get_widget_vec()){
                            widget->on_click_press(window);
                        }
                        break;
                    }
                    case sf::Event::MouseButtonReleased:
                    {
                        for(auto& widget:view->get_widget_vec()){
                            widget->on_click_release(window);
                        }
                        break;
                    }
                    case sf::Event::TextEntered:
                    {
                        for(auto& widget:view->get_widget_vec()){
                            widget->on_type(window,e);
                        }
                        break;
                    }
                }
                if(state == STAGE_CHOOSE_ROOM){
                    ask_for_rooms();
                }
            }
            
            }
            if (e.type == sf::Event::Closed){
                window->close();
            }
        
    model->tick();
    view->render();
    CursorController::get_instance().draw_cursor(window);

}

void MenuController::ask_for_rooms(){
    if (update_timer.getElapsedTime().asSeconds()>UPDATE_INTERVAL_TIME){
        model->ask_rooms();
        update_timer.restart();
    }
}