#pragma once

#include <SFML/Graphics.hpp>
#include "BasicView.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Table.hpp"
#include <functional>
class MenuView:  public BasicView{
public:
    void activate_name_request();
    void disactivate_name_request();
    void activate_rooms();
    void disactivate_rooms();
    sf::String get_name();
    void set_name_button_handler(std::function<void()> inp_handler);
    void set_room_table_handler(std::function<void()> inp_handler);
    void set_create_room_handler(std::function<void()> inp_handler);
    void init() override;    
    void render() override;
    ~MenuView() override;
    MenuView(sf::RenderWindow* inp_window, BasicModel* inp_model){
        window = inp_window;
        model = inp_model;
        init();
    };
private:
    std::shared_ptr<TextBox> name_textbox;
    std::shared_ptr<Button> name_button;
    std::shared_ptr<Table> rooms_table;
    std::shared_ptr<Button> create_room;
    std::shared_ptr<TextBox> room_name;

    void create_name_textbox();
    void create_name_button();
    void create_rooms_table();
    void create_create_room();
    void create_room_name();
    menu_assets menu_media;
    general_assets general_media;
};
