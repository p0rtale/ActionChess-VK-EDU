#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "iostream"
#include "CursorController.hpp"
#include "Variables.hpp"
void TextBox::on_click_press(sf::RenderWindow* window){
    if(active){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (active_zone.contains(window->mapPixelToCoords(mouse_pos))) ? PRESSED: FAR;
        focused = clicked == PRESSED;
    }
    

}

void TextBox::on_click_release(sf::RenderWindow* window){
    if(active){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (active_zone.contains(window->mapPixelToCoords(mouse_pos))) ? OVER : FAR;
    }
    

}


void TextBox::on_mouse_over(sf::RenderWindow* window){
    if(active){
        if(clicked != PRESSED){
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
            clicked = (active_zone.contains(window->mapPixelToCoords(mouse_pos))) ? OVER : FAR;
        }   
    }

}
sf::String TextBox::fit_in_table(sf::Text* box, sf::String str){
    to_show = str;
        box->setString(to_show);
        size_t len_del = 0;
        while(box->getGlobalBounds().width > active_zone.width - BOX_EDGE_OFFSET){
                to_show = str.substring(len_del,str.getSize());
                box->setString(to_show);
                len_del++;

            }
    return to_show;
}
void TextBox::on_type(sf::RenderWindow* window, sf::Event event){
    if(active && focused){
        unsigned int charTyped = event.text.unicode;

        if (charTyped == BACKSPACE_KEY)
        {
            if (data.getSize() > 0)
            {
                data.erase(data.getSize()-1, 1);
            }
        }
        else if (charTyped == ENTER_KEY || charTyped == ESCAPE_KEY)
        {
            focused = false;
        }

        else if (charTyped > 30 && (charTyped < 127 || charTyped > 159))
        {

            if (charTyped != BACKSPACE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && data.getSize() < MAX_STR_SIZE)
            {
                data += charTyped;
            }
            
        }

        //TODO: убрать костыль
        to_show = fit_in_table(&databox,data);


    }
}
void TextBox::draw(sf::RenderWindow* window){
    if(visible){
        window->draw(background);
        sf::String to_show_anim = "";
        if(focused){
            if(cursor_animation.getElapsedTime().asMilliseconds()>CURSOR_ANIMATION_TIME){
                show_cursor ^= 1;
                cursor_animation.restart();
            
            }
            to_show_anim = (show_cursor)? (to_show +'|'):to_show;
            databox.setString(to_show_anim);
            window->draw(databox); // TODO: на каждом таком draw проверять, живое ли окно

        }
        else{
            if(data.getSize() == 0){
                window->draw(hint);
            }
            else{
                databox.setString(to_show);
                window->draw(databox);
            }
            
        }
        if (active){
            if ((clicked == OVER) || (clicked == PRESSED)){
                CursorController::get_instance().set_cursor(sf::Cursor::Text);
            }
        }
    }
}
