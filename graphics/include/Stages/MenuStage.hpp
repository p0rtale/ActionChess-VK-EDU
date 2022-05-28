#pragma once 

#include <SFML/Graphics.hpp>
#include "BasicStage.hpp"
#include "MenuView.hpp"
#include "MenuModel.hpp"
#include "MenuController.hpp"
#include "Client.hpp"
class MenuStage: public BasicStage{

public:
    void init() override;
    BasicStage* run() override;
    ~MenuStage() override;
    MenuStage(sf::RenderWindow* inp_window, Client* inp_c);

protected:
    MenuView* view ;
    MenuController* controller ;
    MenuModel* model ;
};void set_name_button_handler(std::function<void()>);
    void set_room_table_handler(std::function<void()>);
    void set_create_room_handler(std::function<void()>);





