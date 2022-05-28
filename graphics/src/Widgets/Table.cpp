#include <SFML/Graphics.hpp>
#include "Table.hpp"
#include "Variables.hpp"
#include <functional>
#include "Slidebar.hpp"





void Table::on_click_release(sf::RenderWindow* window){
    if(visible && active){
        slider.on_click_release(window);
    }
}
void Table::on_click_press(sf::RenderWindow* window) {
    if(visible && active){
        slider.on_click_press(window);
    }
}
void Table::on_mouse_over(sf::RenderWindow* window){
    if(visible && active){
        slider.on_mouse_over(window);
    }
}
void Table::on_type(sf::RenderWindow* window, sf::Event event){

}
void Table::draw(sf::RenderWindow* window) {
    if(visible){
        table_texture.display();
        window->draw(background);
        slider.draw(window);
        window->draw(text_table);

    }
}