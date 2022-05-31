#pragma once
#include <SFML/Graphics.hpp>
#include "BasicModel.hpp"
#include <functional>
#include "MenuModel.hpp"





class RoomModel: public BasicModel{
//Абстрактный класс для model
public:

    enum RoomModelState{
    ROOM_ACTIVE,
    ROOM_WAITING_FOR_GAME_START
    };
    bool GotNameId(){
        return(player.id!= -1);
    }
    void parse_get_player(std::string data){};
    void init() override {};// TODO: добавить клиент     
    void tick() override  {};// TODO: override 
    RoomModel(Client* inp_c){c = inp_c;};
    ~RoomModel(){
        users.clear();
    } ;
    void set_room_update_handler(std::function<void()> inp_handler){
        rooms_update_handler = inp_handler;
    }
    void create_room(std::string room_name);
    std::vector<User> get_users(){
        return users;
    }
    void ask_rooms(){};
    void set_init(User inp_player, Rooms inp_rooms, std::vector<User> inp_users){
        player = inp_player;
        rooms = inp_rooms;
        users = inp_users;
    }
    User player;
    Rooms rooms;
    std::vector<User> users;
private:

    std::function<void()> rooms_update_handler;
    void parse_rooms(std::string data){};
    RoomModel::RoomModelState state = ROOM_ACTIVE;

};