#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "Variables.hpp"
void Assets::load(){ //TODO: написать хендлеоры ошибок и вставить все файлы в ресурсы exe
    menu.background_image.loadFromFile(MENU_BACKGROUND_IMAGE_PATH);
    menu.name_textbox_background_image.loadFromFile(MENU_NAME_TEXTBOX_BACKGROUND_IMAGE);
    menu.slider_stick_image.loadFromFile(MENU_SLIDEBAR_STICK_IMAGE);
    menu.slider_image.loadFromFile(MENU_SLIDER_IMAGE);
    menu.button_filling.loadFromFile(MENU_BUTTON_FILL_IMAGE);
    menu.button_edge.loadFromFile(MENU_BUTTON_EDGE_IMAGE);
    menu.table_background.loadFromFile(MENU_TABLE_IMAGE);
    general.gost_font.loadFromFile("./fonts/gost.ttf");
}


menu_assets Assets::get_menu_assets(){
    return menu;
}

room_assets Assets::get_room_assets(){
    return room;
}

game_assets Assets::get_game_assets(){
    return game;
}

general_assets Assets::get_general_assets(){
    return general;
}


