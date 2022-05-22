#include <SFML/Graphics.hpp>
#include "MenuView.hpp"
#include "BasicView.hpp"
#include "Assets.hpp"
#include "Variables.hpp"
#include "TextBox.hpp"
#include <memory>
void MenuView::init(){
    menu_media = Assets::get_instance().get_menu_assets();
    general_assets temp = Assets::get_instance().get_general_assets();
    //font = temp.font;
    background_image = menu_media.background_image;
    background_image.setSmooth(true);
    background.setTexture(background_image);
    sf::FloatRect sc = background.getGlobalBounds();
    sf::Vector2f scale_factor = sf::Vector2f(WINDOW_START_WIDTH/sc.width,WINDOW_START_HEIGHT/sc.height);
    background.setScale(scale_factor);
    visible = true;
    //инициализация спрайтов
    sf::Vector2f name_textbox_pos = sf::Vector2f(NAME_TEXTBOX_POS_X, NAME_TEXTBOX_POS_Y);
    sf::Text caption;
    sf::Text hint;
    sf::Text databox;
    sf::Rect<float> act = sf::Rect<float>(name_textbox_pos,name_textbox_pos);
    widgets.push_back(std::make_shared<TextBox>(menu_media.name_textbox_background_image,scale_factor,name_textbox_pos, act,caption,hint,databox));


}

void MenuView::render(){
    window->draw(background);
    for(auto& widget:widgets){
        widget->draw(window);
    }
    window->display();
}

MenuView::~MenuView(){
    widgets.clear();
}
