#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "Variables.hpp"
#include "WindowSwitcher.hpp"
#include "MenuStage.hpp"
#include "Client.hpp"

void WindowSwitcher::init(Client* inp_c){
    c = inp_c;
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_START_WIDTH,WINDOW_START_HEIGHT), window_head_name);
    Stage = new MenuStage(window,c);
}

void WindowSwitcher::run(){
    while(window->isOpen()){
        Stage = Stage->run(); 
    }
}
WindowSwitcher::~WindowSwitcher(){
    delete window;
}
 
