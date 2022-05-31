#pragma once
#include <SFML/Graphics.hpp>
#include "BasicModel.hpp"
#include <functional>




class MenuModel: public BasicModel{
//Абстрактный класс для model
public:

    enum MenuModelState{
    MENU_ACTIVE,
    MENU_WAITING_FOR_SET_PLAYER,
    MENU_WAITING_FOR_GET_ALL_ROOMS,
    MENU_WAITING_FOR_JOIN_ROOM,
    MENU_WAITING_FOR_CREATE_ROOM,
    MENU_JOINED_ROOM
    };
    bool GotNameId(){
        return(player.id!= -1);
    }
    bool JoinedRoom(){
        return state = MENU_JOINED_ROOM;
    }
    void parse_get_player(std::string data);
    void set_player(std::string inp_name);
    void init() override ;// TODO: добавить клиент     
    void tick() override  ;// TODO: override 
    MenuModel(Client* inp_c){c = inp_c;};
    ~MenuModel(){
        rooms.clear();
    } ;
    void parse_jroom(std::string data);
    void set_room_update_handler(std::function<void()> inp_handler){
        rooms_update_handler = inp_handler;
    }
    void create_room(std::string room_name);
    std::vector<Rooms> get_rooms(){
        return rooms;
    }
    void join_room(Rooms room);
    void ask_rooms();
    User player;
    Rooms jroom;
    std::vector<User> jUsers;
private:
    std::function<void()> rooms_update_handler;

    void parse_rooms(std::string data);
    MenuModel::MenuModelState state = MENU_ACTIVE;
    std::vector<Rooms> rooms;
};