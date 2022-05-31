#include "BasicController.hpp"
#include "RoomController.hpp"
#include <SFML/Graphics.hpp>
#include "CursorController.hpp"
#include <functional>
#include <iostream>
#include <thread>
#include "Assets.hpp"
#include "Variables.hpp"
#include <MenuController.hpp>

void RoomController::init(){
    //state = STAGE_ASK_NAME;
    //view->activate_name_request();
    //std::function <void ()> handler = std::bind(&RoomController::handle_name_enter,this);
    //view->set_name_button_handler(handler);
   // handler = std::bind(&RoomController::handle_create_room,this);
    //view->set_create_room_handler(handler);
    //handler = std::bind(&RoomView::set_rooms_table_from_model ,view);
    //model->set_room_update_handler(handler);
}    





void RoomController::handle_msg_send(){
    // sf::String player_name = view->get_name();
    // if (player_name.getSize() == 0){ //TODO: реализовать
    //     err =L"Пустое имя";
    //     std::thread t(throw_error,err);
    //     t.detach();
    // }
    // else{
    //     state = STAGE_WAIT_NAME_CONFIRMATION;
    //     model->set_player(player_name);


    // }    
}

// void RoomController::handle_create_room(){
//     sf::String room_name = view->get_room_name();
//     if (room_name.getSize() == 0){ //TODO: реализовать
//         err =L"Пустое имя комнаты";
//         //state = STAGE_FREEZE;
//         std::thread t(throw_error,err);
//         t.detach();
//     }
//     else{
//         model->create_room(room_name.toAnsiString());
//         view->disactivate_rooms();
//     }   
// }
bool RoomController::run(){
    
    sf::Event e;
        while (window->pollEvent(e))
        {            
            if((state == STAGE_ASK_NAME)||(state == STAGE_CHOOSE_ROOM)){
                CursorController::get_instance().reset_cursor();

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
                // if(state == STAGE_CHOOSE_ROOM){
                //     ask_for_rooms();
                // }
           }
           else{
               CursorController::get_instance().set_cursor(sf::Cursor::Wait);
            //    if(state == STAGE_WAIT_ROOM_WAITING_FOR_GAME_START){
            //        if (model->GotNameId()){
            //          view ->activate_rooms();
            //         state = STAGE_CHOOSE_ROOM;
            //        }
            //    }
            //    else if(state == STAGE_WAIT_ROOM_CONFIRMATION){
            //     //    if (model->GotNameId()){
            //     //      view ->activate_rooms();
            //     //     state = STAGE_CHOOSE_ROOM;
            //     //    }
            //    }
           }            
            }
            if (e.type == sf::Event::Closed){
                window->close();
            }
        
    model->tick();
    view->render();
    CursorController::get_instance().draw_cursor(window);
    return true;
}

// void RoomController::ask_for_rooms(){
//     if (update_timer.getElapsedTime().asSeconds()>UPDATE_INTERVAL_TIME){
//         model->ask_rooms();
//         update_timer.restart();
//     }
// }