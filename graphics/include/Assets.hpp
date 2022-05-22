#pragma once 

#include <SFML/Graphics.hpp>
struct menu_assets{
    sf::Texture background_image;
    sf::Texture name_textbox_background_image;
};

struct room_assets{

};

struct game_assets{

};

struct general_assets{
    sf::Font font; 
};

class Assets{
/*
//Класс синглтон для загрузки, храниния шрифтов, картинок, мызуки и т.д.
//Окна и виджеты будут брать отсюда через геттеры
*/

public:
    void load();
    static Assets& get_instance(){
        static Assets instance;
        return instance;
    }    
    menu_assets get_menu_assets();
    room_assets get_room_assets();
    game_assets get_game_assets();
    general_assets get_general_assets();

private:
    menu_assets menu;
    room_assets room;
    game_assets game;
    general_assets general;
    Assets(){load();};
    ~Assets() = default;
    Assets(Assets const& other) = delete;
    Assets &operator=(Assets const& other) = delete;
    Assets(Assets&& that) = delete;
    Assets &operator=(Assets&& that) = delete;
    friend void swap(Assets& lhs, Assets& rhs) = delete;

};

