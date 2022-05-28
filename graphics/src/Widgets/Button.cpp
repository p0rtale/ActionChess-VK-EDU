#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Variables.hpp"
#include "Assets.hpp"
#include <functional>

#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "CursorController.hpp"
#include "Variables.hpp"
void Button::on_click_press(sf::RenderWindow* window){
    if(active && visible){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (background.getGlobalBounds().contains(window->mapPixelToCoords(mouse_pos))) ? PRESSED: FAR;
        animate_click();
    }
    

}

void Button::on_click_release(sf::RenderWindow* window){
    if(active&& visible){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (background.getGlobalBounds().contains(window->mapPixelToCoords(mouse_pos))) ? OVER : FAR;
        if (clicked == OVER){
            handler();
        }
        animate_click();

    }
    

}


void Button::on_mouse_over(sf::RenderWindow* window){
    if(active&& visible){
        if(clicked != PRESSED){
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
            clicked = (background.getGlobalBounds().contains(window->mapPixelToCoords(mouse_pos))) ? OVER : FAR;
            animate_click();
        }   
    }

}

void Button::animate_click(){
    switch(clicked){
            case OVER:
                background.setColor(fill_when_mouse_over);
                background.setScale(scale_factor);
                edge.setScale(scale_factor);
                caption.setScale(sf::Vector2f(1.f,1.f));
                break;
            case FAR:
                background.setColor(fill_color_default);
                background.setScale(scale_factor);
                edge.setScale(scale_factor);
                caption.setScale(sf::Vector2f(1.f,1.f));
                break;
            case PRESSED:
                background.setColor(fill_when_mouse_over);
                background.setScale(scale_factor.x*BUTTON_SHRINK_SCALE_WHEN_PRESSED,scale_factor.y*BUTTON_SHRINK_SCALE_WHEN_PRESSED);
                caption.setScale(BUTTON_SHRINK_SCALE_WHEN_PRESSED,BUTTON_SHRINK_SCALE_WHEN_PRESSED);
                edge.setScale(scale_factor.x*BUTTON_SHRINK_SCALE_WHEN_PRESSED,scale_factor.y*BUTTON_SHRINK_SCALE_WHEN_PRESSED);

                break;
            
        }
}

void Button::on_type(sf::RenderWindow* window, sf::Event event){
    }


void Button::draw(sf::RenderWindow* window){
    if(visible){
        
        window->draw(background);
        window->draw(edge);
        window->draw(caption);
    }
}

