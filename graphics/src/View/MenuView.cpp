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
#include "Table.hpp"
#include <iostream>
void empty(){}; //для первоначальной инициилизации хендлеров кнопок

void MenuView::init(){
    menu_media = Assets::get_instance().get_menu_assets();
    general_media = Assets::get_instance().get_general_assets();
    //font = temp.font;
    background_image = menu_media.background_image;
    background_image.setSmooth(true);
    background.setTexture(background_image);
    sf::FloatRect sc = background.getGlobalBounds();
    scale_factor = sf::Vector2f(WINDOW_START_WIDTH/sc.width,WINDOW_START_HEIGHT/sc.height);//TODO: убрать костыль scale factor
    background.setScale(scale_factor);
    visible = true;
    //инициализация спрайтов
    create_name_textbox();
    create_name_button();
    create_rooms_table();


}

void MenuView::render(){
    if(visible){
        window->draw(background);
        for(auto& widget:widgets){
            widget->draw(window);
        }
        window->display();
    }
    else{
        window->clear();
    }
}

MenuView::~MenuView(){
    widgets.clear();
}

void MenuView::activate_name_request(){
    disactivate_rooms();
    name_textbox->set_active(true);
    name_textbox->set_visible(true);
    name_button->set_active(true);
    name_button->set_visible(true);
    widgets.push_back(name_textbox);
    widgets.push_back(name_button);
}
void MenuView::disactivate_name_request(){
    name_textbox->set_active(false);
    name_textbox->set_visible(false);
    name_button->set_active(false);
    name_button->set_visible(false);
    widgets.clear();
}
void MenuView::activate_rooms(){
    disactivate_name_request();
    rooms_table->set_active(true);
    rooms_table->set_visible(true);    
    widgets.push_back(rooms_table);
}
void MenuView::disactivate_rooms(){
    rooms_table->set_active(false);
    rooms_table->set_visible(false);    
    widgets.clear();
}



void MenuView::create_name_textbox(){
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
    name_textbox = std::make_shared<TextBox>(menu_media.name_textbox_background_image,scale_factor,name_textbox_pos, act,caption,hint,databox);
}

void MenuView::create_name_button(){
    std::function <void ()> f = std::bind(&empty);
    sf::Text caption;
    caption.setFillColor(sf::Color::Black);
    caption.setFont(general_media.gost_font);
    caption.setCharacterSize(MENU_NAME_BUTTON_CHARACTER_SIZE);
    caption.setString(NAME_BUTTON_CAPTION_STRING);
    name_button = std::make_shared<Button>(menu_media.button_filling, menu_media.button_edge,sf::Color(255,255,255), sf::Color(50,50,50,50),sf::Color(255,255,255,50), sf::Color(255,255,255,100), sf::Vector2f(BUTTON_SHRINK_SCALE_WHEN_PRESSED,BUTTON_SHRINK_SCALE_WHEN_PRESSED), scale_factor, sf::Vector2f(MENU_BUTTON_POS_X,MENU_BUTTON_POS_Y), caption,f);
}
void MenuView::create_rooms_table(){
    std::function <void ()> f = std::bind(&empty);
    sf::Text caption;
    caption.setFillColor(sf::Color::Black);
    caption.setFont(general_media.gost_font);
    caption.setCharacterSize(MENU_NAME_BUTTON_CHARACTER_SIZE);
    caption.setString(NAME_BUTTON_CAPTION_STRING);
    rooms_table = std::make_shared<Table>(menu_media.table_background, menu_media.slider_stick_image,menu_media.slider_image, sf::Vector2f(1300,100), sf::Rect<float>(120,220,1000,730),sf::Color(255,255,255,50), \
    sf::Color(255,255,255,0),scale_factor, sf::Vector2f(MENU_TABLE_POS_X,MENU_TABLE_POS_Y), caption,f);
    
}
void MenuView::create_create_room(){
    
}

//void MenuView::create_room_name();


void MenuView::set_name_button_handler(std::function<void()> inp_handler){
    name_button->set_handler(inp_handler);
}
void MenuView::set_room_table_handler(std::function<void()> inp_handler){}
void MenuView::set_create_room_handler(std::function<void()> inp_handler){}

sf::String MenuView::get_name(){
    return name_textbox->get_data();
}
