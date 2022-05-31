#pragma once 

#include <SFML/Graphics.hpp>
#include "BasicStage.hpp"
#include "RoomView.hpp"
#include "RoomModel.hpp"
#include "RoomController.hpp"
#include "Client.hpp"
class RoomStage: public BasicStage{

public:
    void init() override;
    BasicStage* run() override;
    ~RoomStage() override;
    RoomStage(sf::RenderWindow* inp_window, Client* inp_c,User player, std::vector<User> users, Rooms room);

protected:
bool nado =true;
    RoomView* view ;
    RoomController* controller ;
    RoomModel* model ;
};





