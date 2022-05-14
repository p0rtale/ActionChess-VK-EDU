#pragma once 

#include <SFML/Graphics.hpp>
#include "BasicWindow.hpp"

class MainMenu: BasicWindow{
    class BasicWindow
{

public:
    MainMenu* event_handler() override;
    void draw() override;

private:
    MainMenu();
    ~MainMenu();
    
    Player player;
    vector<Room> rooms;
};


}