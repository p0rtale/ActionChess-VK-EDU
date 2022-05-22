#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"

void TextBox::on_click_press(sf::RenderWindow* window){
    if(clicked == OVER){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (active_zone.contains(window->mapPixelToCoords(mouse_pos))) ? OVER: FAR;
        focused = true;
    } 
    else{
        focused = false;
    }  
}


void TextBox::on_mouse_over(sf::RenderWindow* window){
    if(clicked != PRESSED){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (active_zone.contains(window->mapPixelToCoords(mouse_pos))) ? OVER : FAR;
    }   
}

void TextBox::on_type(){

}
void TextBox::draw(sf::RenderWindow* window) const{
    window->draw(background);

}
