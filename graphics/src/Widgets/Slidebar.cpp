#include <SFML/Graphics.hpp>
#include "Slidebar.hpp"
#include "Variables.hpp"
#include "Assets.hpp"
#include <iostream>

void Slidebar::on_click_release(sf::RenderWindow* window){

    clicked = FAR;
}


void Slidebar::on_click_press(sf::RenderWindow* window) {
    if(active && visible){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        sf::Vector2f coordinates = window->mapPixelToCoords(mouse_pos); 
        clicked = (slider.getGlobalBounds().contains(coordinates)) ? PRESSED : FAR;
        mouse_prev_pos = coordinates.y;
        mouse_delta = 0;
        if((clicked == PRESSED) && (slider.getGlobalBounds().top+mouse_delta >= slide_stick.getGlobalBounds().top) && (slider.getGlobalBounds().top+mouse_delta<=slide_stick.getGlobalBounds().top+slide_stick.getGlobalBounds().height)){
            slider.setPosition(slider.getGlobalBounds().left,slider.getGlobalBounds().top+mouse_delta);
        }
    }
}


void Slidebar::on_mouse_over(sf::RenderWindow* window){
    if(active && visible){
        if (clicked == PRESSED){
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
            sf::Vector2f coordinates = window->mapPixelToCoords(mouse_pos); 
            mouse_delta = coordinates.y - mouse_prev_pos;
            if((clicked == PRESSED) && (slider.getGlobalBounds().top+mouse_delta >= slide_stick.getGlobalBounds().top) && (slider.getGlobalBounds().top+slider.getGlobalBounds().height+mouse_delta<=slide_stick.getGlobalBounds().top+slide_stick.getGlobalBounds().height)){
                slider.setPosition(slider.getGlobalBounds().left,slider.getGlobalBounds().top+mouse_delta);
            
            mouse_delta = 0;
            mouse_prev_pos = coordinates.y;
            }
        }
    }
}


void Slidebar::on_type(sf::RenderWindow* window, sf::Event event){
    
}


void Slidebar::draw(sf::RenderWindow* window) {
    window->draw(slide_stick);
    window->draw(slider);
}


