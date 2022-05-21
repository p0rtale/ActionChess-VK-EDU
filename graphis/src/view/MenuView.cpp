#include <SFML/Graphics.hpp>
#include "MenuView.hpp"
#include "BasicView.hpp"
#include "Assets.hpp"

void MenuView::init(){
    menu_media = Assets::get_instance().get_menu_assets();
    general_assets temp = Assets::get_instance().get_general_assets();
    //font = temp.font;
    background_image = menu_media.background_image;
    background_image.setSmooth(true);
    background.setTexture(background_image);
    visible = true;
    //инициализация спрайтов

}

void MenuView::render(){
    window->draw(background);
    window->display();
}

MenuView::~MenuView(){

}
