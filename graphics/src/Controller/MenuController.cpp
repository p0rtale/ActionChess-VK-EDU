#include "BasicController.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>
#include "CursorController.hpp"

void MenuController::init(){
    StageState state = STAGE_ACTIVE;
}    
void MenuController::run(){
    CursorController::get_instance().reset_cursor();
    sf::Event e;
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
                case sf::Event::Closed:
                {
                    window->close();
                    break;
                }
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

    view->render();
    CursorController::get_instance().draw_cursor(window);

}