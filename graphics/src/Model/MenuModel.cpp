#include <SFML/Graphics.hpp>
#include "MenuModel.hpp"
#include <Message.hpp>
#include <iostream>
#include "rapidjson/document.h"
#include <mutex>

/*
Request:
{
	“type”: “get-all-rooms”, 
	“data”: [пусто]
}

Response:
{
	“type”: “get-all-rooms”,
	“status”: …,
	“data”: {
rooms: [
	{ “id”: int, “name”: string, “users-num”: int }
]
}
}

*/



void MenuModel::parse_rooms(std::string data){//TODO: перенести парсер в класс клиента, чтобы модель не занималась парсингом данных.
    rapidjson::Document doc;
    std::cout<<"1"<<std::endl;
    auto& allocator = doc.GetAllocator();
    std::cout<<"1"<<std::endl;
    if (!doc.Parse(data.data()).HasParseError() &&
        doc.HasMember("rooms") && 
        doc["rooms"].IsArray()) {
            rooms.clear();
            if (doc["rooms"].GetArray().Size() == 0){
                std::cout<<"3"<<std::endl;
                
                return;
            }
            for(int i=0;i<doc["rooms"].GetArray().Size();i++){
                //TODO: добавить проверки
                
                Rooms inp_room;
                std::vector<User> inp_users;
                inp_room.id = doc["rooms"].GetArray()[i]["room"]["id"].GetInt();
                inp_room.name = doc["rooms"].GetArray()[i]["room"]["name"].GetString();
                for(int j=0;j<doc["rooms"].GetArray()[i]["room"]["users"].GetArray().Size();j++){
                    inp_users.push_back(User(doc["rooms"].GetArray()[i]["room"]["users"].GetArray()[j]["user"]["name"].GetString(),doc["rooms"].GetArray()[i]["room"]["users"].GetArray()[j]["user"]["id"].GetInt()));
                }
                inp_room.users = inp_users;
                inp_room.users_num= doc["rooms"].GetArray()[i]["room"]["users-num"].GetInt();
                inp_room.max_users_num = doc["rooms"].GetArray()[i]["room"]["max-users-num"].GetInt();
                rooms.push_back(inp_room);
                
                
            } 
        rooms_update_handler();
        std::cout<<"ROOMS "<<rooms.size()<<std::endl;
    }
}
void MenuModel::set_player(std::string inp_name){
    player.name = inp_name;
    player.id = -1;
    c->ask_id();
    state = MenuModel::MenuModelState::MENU_WAITING_FOR_SET_PLAYER;
}

void MenuModel::ask_rooms(){
    c->get_all_rooms();
    state = MenuModel::MenuModelState::MENU_WAITING_FOR_GET_ALL_ROOMS;
    
}
void MenuModel::init(){};// TODO: добавить клиент     
void MenuModel::tick(){
    if(c->queue_mutex.try_lock()){

    
        for(int i =0; i< c->get_response_queue()->size();i++){
            std::cout<<"EWE"<<std::endl;
            Response to_process = c->get_response_queue()->front();
            if(to_process.m_status == ResponseStatus::OK){
                switch(to_process.m_type){
                    case RequestType::GET_ALL_ROOMS:{
                        parse_rooms(to_process.m_jsonData);
                        break;
                    }
                    case RequestType::GET_ID
                }
            }
            else{
                std::cout<<(int)to_process.m_status<<std::endl;
            }

            c->get_response_queue()->pop_front();
        }
        c->queue_mutex.unlock();
    }
}

void MenuModel::create_room(std::string room_name){
    c->create_room(room_name,player.name);
    state = MenuModel::MenuModelState::MENU_WAITING_FOR_CREATE_ROOM;
}
