#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "Variables.hpp"
void Assets::load(){
    menu.background_image.loadFromFile(MENU_BACKGROUND_IMAGE_PATH);

    general.font.loadFromFile(GENERAL_FONT_PATH);
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


