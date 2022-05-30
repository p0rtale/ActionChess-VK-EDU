#pragma once
#include <SFML/Graphics.hpp>
#include "BasicModel.hpp"
#include <functional>


struct User{
    std::string name;
    int id;
    std::string name_id;
    User(std::string inp_name, int inp_id){
        name = inp_name;
        id = inp_id;
        name_id = inp_name +"#"+ std::to_string(id);
    }
    User() = default;
};
struct Rooms{
    std::string name;
    int id;
    std::vector<User> users;
    int users_num;
    int max_users_num;
    Rooms() = default;
   
};

class MenuModel: public BasicModel{
//Абстрактный класс для model
public:

    enum MenuModelState{
    MENU_ACTIVE,
    MENU_WAITING_FOR_SET_PLAYER,
    MENU_WAITING_FOR_GET_ALL_ROOMS,
    MENU_WAITING_FOR_JOIN_ROOM,
    MENU_WAITING_FOR_CREATE_ROOM
    };
    void set_player(std::string inp_name);
    void init() override ;// TODO: добавить клиент     
    void tick() override  ;// TODO: override 
    MenuModel(Client* inp_c){c = inp_c;};
    ~MenuModel(){
        rooms.clear();
    } ;
    void set_room_update_handler(std::function<void()> inp_handler){
        rooms_update_handler = inp_handler;
    }
    void create_room(std::string room_name);
    std::vector<Rooms> get_rooms(){
        return rooms;
    }
    void ask_rooms();
private:
    std::function<void()> rooms_update_handler;

    void parse_rooms(std::string data);
    MenuModel::MenuModelState state = MENU_ACTIVE;
    std::vector<Rooms> rooms;
    User player;
};