#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "Variables.hpp"
#include "WindowSwitcher.hpp"
#include "MenuStage.hpp"


void WindowSwitcher::init(){
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_START_WIDTH,WINDOW_START_HEIGHT), window_head_name);
    Stage = new MenuStage(window);
}

void WindowSwitcher::run(){
    //while(window->isOpen()){
        Stage = Stage->run(); 
    //}
}
WindowSwitcher::~WindowSwitcher(){
    delete window;
}
 
