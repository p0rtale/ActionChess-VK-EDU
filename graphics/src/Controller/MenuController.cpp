#include "BasicController.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>

void MenuController::init(){
    StageState state = STAGE_ACTIVE;
}    
void MenuController::run(){
    sf::Event e;
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
                case sf::Event::Closed:
                {
                    window->close();
                    break;
                }
                case sf::Event::MouseMoved:
                {
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {

                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    break;
                }
                case sf::Event::TextEntered:
                {

                    break;
                }
            }
        }
    view->render();
}