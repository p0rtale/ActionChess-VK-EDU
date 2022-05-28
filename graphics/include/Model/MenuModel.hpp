#pragma once
#include <SFML/Graphics.hpp>
#include "BasicModel.hpp"

struct User{
    std::string name ="";
    int id;
};
struct Rooms{
    std::string name;
    int id;
    std::vector<User> users;
    int users_num;
    int max_users_num;

};

class MenuModel: public BasicModel{
//Абстрактный класс для model
public:
    void set_player(std::string inp_name){
        player.name = inp_name;
        player.id = -1;
    }
    void init() override {};// TODO: добавить клиент     
    void tick() override {} ;// TODO: override 
    MenuModel(Client* inp_c){c = inp_c;};
    ~MenuModel(){
        rooms.clear();
    } ;
private:
    std::vector<Rooms> rooms;
    User player;
};