#include <SFML/Graphics.hpp>
#include "MenuView.hpp"
#include "BasicView.hpp"
#include "Assets.hpp"
#include "Variables.hpp"
#include "TextBox.hpp"
#include "Slidebar.hpp"
#include <memory>
#include <functional>
#include "Button.hpp"

void empty(){}; //TODO: delete

void MenuView::init(){
    menu_media = Assets::get_instance().get_menu_assets();
    general_media = Assets::get_instance().get_general_assets();
    //font = temp.font;
    background_image = menu_media.background_image;
    background_image.setSmooth(true);
    background.setTexture(background_image);
    sf::FloatRect sc = background.getGlobalBounds();
    sf::Vector2f scale_factor = sf::Vector2f(WINDOW_START_WIDTH/sc.width,WINDOW_START_HEIGHT/sc.height);//TODO: убрать костыль scale factor
    background.setScale(scale_factor);
    visible = true;
    //инициализация спрайтов
    sf::Vector2f name_textbox_pos = sf::Vector2f(NAME_TEXTBOX_POS_X, NAME_TEXTBOX_POS_Y);
    sf::Text caption;
    sf::Text hint;
    sf::Text databox;
    databox.setFillColor(sf::Color::Black);
    databox.setFont(general_media.gost_font);
    databox.setCharacterSize(NAME_TEXTBOX_CHARACTER_SIZE);
    hint.setFillColor(sf::Color(GREY_COLOR_RGB_VALUE,GREY_COLOR_RGB_VALUE,GREY_COLOR_RGB_VALUE));
    hint.setFont(general_media.gost_font);
    hint.setCharacterSize(NAME_TEXTBOX_CHARACTER_SIZE);
    hint.setString(NAME_TEXTBOX_HINT_STRING);
    sf::Rect<float> act = sf::Rect<float>(NAME_TEXTBOX_ACTBOX_X*scale_factor.x, NAME_TEXTBOX_ACTBOX_Y*scale_factor.y, NAME_TEXTBOX_ACTBOX_WIDTH*scale_factor.x, NAME_TEXTBOX_ACTBOX_HEIGHT*scale_factor.y);
    widgets.push_back(std::make_shared<TextBox>(menu_media.name_textbox_background_image,scale_factor,name_textbox_pos, act,caption,hint,databox));
    widgets.push_back(std::make_shared<Slidebar>(menu_media.slider_stick_image,menu_media.slider_image,scale_factor,sf::Vector2f(2400.f,1050.f)));
    std::function <void ()> f = std::bind(&empty);
    caption.setFillColor(sf::Color::Black);
    caption.setFont(general_media.gost_font);
    caption.setCharacterSize(MENU_NAME_BUTTON_CHARACTER_SIZE);
    caption.setString(NAME_BUTTON_CAPTION_STRING);
    widgets.push_back(std::make_shared<Button>(menu_media.button_filling, menu_media.button_edge,sf::Color(255,255,255), sf::Color(50,50,50,50),sf::Color(255,255,255,50), sf::Color(255,255,255,100), sf::Vector2f(BUTTON_SHRINK_SCALE_WHEN_PRESSED,BUTTON_SHRINK_SCALE_WHEN_PRESSED), scale_factor, sf::Vector2f(MENU_BUTTON_POS_X,MENU_BUTTON_POS_Y), caption,f));
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
