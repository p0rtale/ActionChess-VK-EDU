#include "BasicController.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>
#include "CursorController.hpp"
#include <functional>

void MenuController::init(){
    StageState state = STAGE_ACTIVE;
    view->activate_name_request();
    std::function <void ()> handler = std::bind(&MenuController::handle_name_enter,this);
    view->set_name_button_handler(handler);
}    

void MenuController::handle_name_enter(){
    sf::String player_name = view->get_name();
    if (player_name.getSize() == 0){ //TODO: реализовать
        err ="Пустое имя";
        //state = STAGE_FREEZE;
        //thread.launch();
    }
    else{
        model->set_player(player_name);
        view ->activate_rooms();
    }
    
    
}
void MenuController::run(){
    CursorController::get_instance().reset_cursor();
    sf::Event e;
        while (window->pollEvent(e))
        {            
            if(state == STAGE_ACTIVE){
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
            }
            else{
                if(err.getSize() == 0){
                        state = STAGE_ACTIVE;

                }
            }
            if (e.type == sf::Event::Closed){
                window->close();
            }
        }

    view->render();
    CursorController::get_instance().draw_cursor(window);

}

void throw_error(sf::String err){
    sf::RenderWindow error_window(sf::VideoMode(800,600), "ERROR");
    sf::Text caption(err,Assets::get_instance().get_general_assets().gost_font,30);
    error_window.clear();
    error_window.draw(caption);
    error_window.display();
    sf::Event e;
    while (error_window.isOpen()){
        while (error_window.pollEvent(e)){
            if (e.type == sf::Event::Closed){
                    error_window.close();
                }
            error_window.display();
        }
    }
    

}