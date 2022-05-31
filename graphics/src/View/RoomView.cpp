#include <SFML/Graphics.hpp>
#include "RoomView.hpp"
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
static void empty(){}; //для первоначальной инициилизации хендлеров кнопок

void RoomView::init(){
    menu_media = Assets::get_instance().get_menu_assets();
    general_media = Assets::get_instance().get_general_assets();
    room_media = Assets::get_instance().get_room_assets();
    //font = temp.font;
    background_image = room_media.background_image;
    background_image.setSmooth(true);
    background.setTexture(background_image);
    sf::FloatRect sc = background.getGlobalBounds();
    scale_factor = sf::Vector2f(WINDOW_START_WIDTH/sc.width,WINDOW_START_HEIGHT/sc.height);//TODO: убрать костыль scale factor
    background.setScale(scale_factor);
    visible = true;
    //инициализация спрайтов
    create_chat_textbox();
    create_ready_button();
    //create_user_table();
    create_leave_room();

}

void RoomView::render(){
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

RoomView::~RoomView(){
    widgets.clear();
}



void RoomView::create_chat_textbox(){
        sf::Vector2f chat_textbox_pos = sf::Vector2f(117, 1412);
    sf::Text caption;
    sf::Text hint;
    sf::Text databox;
    databox.setFillColor(sf::Color::Black);
    databox.setFont(general_media.gost_font);
    databox.setCharacterSize(NAME_TEXTBOX_CHARACTER_SIZE);
    hint.setFillColor(sf::Color(GREY_COLOR_RGB_VALUE,GREY_COLOR_RGB_VALUE,GREY_COLOR_RGB_VALUE));
    hint.setFont(general_media.gost_font);
    hint.setCharacterSize(20);
    hint.setString(L"Введите сообщение");
    sf::Rect<float> act = sf::Rect<float>(177*scale_factor.x, 1412*scale_factor.y, 560*scale_factor.x, 56*scale_factor.y);
    sf::Texture empty;

    chat_textbox= std::make_shared<TextBox>(empty,scale_factor,chat_textbox_pos, act,caption,hint,databox);
    widgets.push_back(chat_textbox);
}

void RoomView::create_ready_button(){
    std::function <void ()> f = std::bind(&empty);
    sf::Text caption;
    caption.setFillColor(sf::Color::Green);
    caption.setStyle(sf::Text::Bold);
    caption.setFont(general_media.gost_font);
    caption.setCharacterSize(MENU_NAME_BUTTON_CHARACTER_SIZE);
    caption.setString(L"Изменить готовность");
    ready_button = std::make_shared<Button>(menu_media.button_filling, menu_media.button_edge,sf::Color(255,255,255), sf::Color(50,50,50,100),sf::Color(255,255,255,250), sf::Color(255,255,255,100), sf::Vector2f(BUTTON_SHRINK_SCALE_WHEN_PRESSED,BUTTON_SHRINK_SCALE_WHEN_PRESSED), scale_factor, sf::Vector2f(1600,700), caption,f);
    widgets.push_back(ready_button);
}
void RoomView::create_user_table(){
    std::function <void ()> f = std::bind(&empty);
    sf::Text caption;
    caption.setFillColor(sf::Color::Black);
    caption.setFont(general_media.gost_font);
    caption.setCharacterSize(MENU_NAME_BUTTON_CHARACTER_SIZE);
    caption.setString(NAME_BUTTON_CAPTION_STRING);
    user_table = std::make_shared<Table>(menu_media.table_background, menu_media.slider_stick_image,menu_media.slider_image, sf::Vector2f(1300,100), sf::Rect<float>(120,220,1000,330),sf::Color(255,255,255,50), \
    sf::Color(255,255,255,0),scale_factor, sf::Vector2f(1300,800), caption,f);
    widgets.push_back(user_table);
    
}
void RoomView::create_leave_room(){
    std::function <void ()> f = std::bind(&empty);
    sf::Text caption;
    caption.setFillColor(sf::Color::Black);
    caption.setFont(general_media.gost_font);
    caption.setCharacterSize(MENU_NAME_BUTTON_CHARACTER_SIZE);
    caption.setString(L"Выйти из комнаты");
    leave_room = std::make_shared<Button>(menu_media.button_filling, menu_media.button_edge,sf::Color(255,255,0), sf::Color(50,50,50,50),sf::Color(255,255,255,50), sf::Color(255,255,255,100), sf::Vector2f(BUTTON_SHRINK_SCALE_WHEN_PRESSED,BUTTON_SHRINK_SCALE_WHEN_PRESSED), scale_factor, sf::Vector2f(2200,1000), caption,f);
    widgets.push_back(leave_room);
}


void RoomView::set_ready_button_handler(std::function<void()> inp_handler){};
void RoomView::set_send_msg_handler(std::function<void()> inp_handler){};
void RoomView::set_leave_room_handler(std::function<void()> inp_handler){
    leave_room->set_handler(inp_handler);
}

sf::String RoomView::get_msg(){
    return chat_textbox->get_data();
}

