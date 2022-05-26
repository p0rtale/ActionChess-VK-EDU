#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "iostream"
#include "CursorController.hpp"

void TextBox::on_click_press(sf::RenderWindow* window){
    if(active){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (active_zone.contains(window->mapPixelToCoords(mouse_pos))) ? PRESSED: FAR;
        focused = clicked == PRESSED;
    }
    

}


void TextBox::on_mouse_over(sf::RenderWindow* window){
    if(active){
        if(clicked != PRESSED){
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
            std::cout<<active_zone.top<<' '<<active_zone.left<<"  "<<window->mapPixelToCoords(mouse_pos).x<<" "<<window->mapPixelToCoords(mouse_pos).y<<std::endl;
            clicked = (active_zone.contains(window->mapPixelToCoords(mouse_pos))) ? OVER : FAR;
        }   
    }

}

void TextBox::on_type(sf::RenderWindow* window){

}
void TextBox::draw(sf::RenderWindow* window){
    window->draw(background);
    if(focused){
        if(cursor_animation.getElapsedTime().asMilliseconds()>CURSOR_ANIMATION_TIME){
            show_cursor ^= 1;
            cursor_animation.restart();
           
        }
    }
    sf::String to_show_anim = (show_cursor)? (to_show +'|'):to_show;
    databox.setString(to_show_anim);
    window->draw(databox); // TODO: на каждом таком draw проверять, живое ли окно
    if ((clicked == OVER) || (clicked == PRESSED))
    {
        CursorController::get_instance().set_cursor(sf::Cursor::Text);
    }
    
}
