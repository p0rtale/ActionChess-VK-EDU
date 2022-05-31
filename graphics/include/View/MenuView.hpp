#pragma once

#include <SFML/Graphics.hpp>
#include "BasicView.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Table.hpp"
#include <functional>
#include "MenuModel.hpp"
class MenuView:  public BasicView{
public:
    void activate_name_request();
    void disactivate_name_request();
    void activate_rooms();
    void disactivate_rooms();
    sf::String get_name();
    sf::String get_room_name();
    void set_name_button_handler(std::function<void()> inp_handler);
    void set_room_table_handler(std::function<void()> inp_handler);
    void set_create_room_handler(std::function<void()> inp_handler);
    void set_rooms_table_from_model(){
        rooms_table->set_rooms(model->get_rooms());
    }

    void init() override;    
    void render() override;
    ~MenuView() override;
    MenuView(sf::RenderWindow* inp_window, MenuModel* inp_model){
        window = inp_window;
        model = inp_model;
        init();
    };
        std::shared_ptr<Table> rooms_table;

private:
    MenuModel* model;
    std::shared_ptr<TextBox> name_textbox;
    std::shared_ptr<Button> name_button;
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
