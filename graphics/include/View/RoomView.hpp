#pragma once

#include <SFML/Graphics.hpp>
#include "BasicView.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Table.hpp"
#include <functional>
#include "RoomModel.hpp"
class RoomView:  public BasicView{
public:
    sf::String get_msg();
    sf::String get_room_name();
    void set_ready_button_handler(std::function<void()> inp_handler);
    void set_send_msg_handler(std::function<void()> inp_handler);
    void set_leave_room_handler(std::function<void()> inp_handler);
    void set_user_table_from_model(){
        user_table->set_user(model->get_users());
    }
    void init() override;    
    void render() override;
    ~RoomView() override;
    RoomView(sf::RenderWindow* inp_window, RoomModel* inp_model){
        window = inp_window;
        model = inp_model;
        init();
    };
private:
    RoomModel* model;
    std::shared_ptr<TextBox> chat_textbox;
    std::shared_ptr<Button> ready_button;
    std::shared_ptr<Table> user_table;
    std::shared_ptr<Button> leave_room;
    

    void create_chat_textbox();
    void create_ready_button();
    void create_user_table();
    void create_leave_room();
    menu_assets menu_media;
    room_assets room_media;
    general_assets general_media;
};
