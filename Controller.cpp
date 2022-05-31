#include "Controller.hpp"


void Controller::send_message_move(int id, Tile pos_to){
        std::array<unsigned int,2> pos_to_ = {pos_to.row, pos_to.column};
        c.move_figure(int id, std::array<unsigned int,2> pos_to)
}

void Controller::tick(){
    if (c->queue_mutex.try_lock()){

        for (int i =0; i < c->get_response_queue()->size(); ++i){
        std::cout<< "EWE" << std::endl;
        Responce to_process = c->get_response_queue()->frint();
        if (to_process.m_status = ResponseStatus::OK){
            switch(to_process.m_type){
                case RequestType::LISTEN_MOVE:{
                    parse_listen_move(to_process.m_jsinData);
                }
                case RequestType::DELETE_FIGURE:{
                    parse_delete_figure(to_process.m_jsinData);
                }
                case RequestType::TIMEOUT_MOVE:{
                    parse_timeout_move(to_process.m_jsinData);
                }
                case RequestType::GAME_OVER:{
                    parse_game_over(to_process.m_jsinData);
                }
            }
        }
        }
    }
}


void Controller::parse_listen_move(std::string data){
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();
    if (!doc.Parse(data.data()).HasParseError())
        if (doc.HasMember("id")) {
        message.data_listen_move.id = doc["id"].getInt();   
        }
        if (doc.HasMember("pos-to"))  {
            message.data_listen_move.row = doc["pos-to"]["row"].getInt();
            message.data_listen_move.column = doc["pos-to"]["column"].getInt() 
        }
        if (doc.HasMember("time")) {
            message.data_listen_move.id = doc["time"].getInt();   
        }
    }      
}
void Controller::parse_delete_figure(std::string data){
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();
    if (!doc.Parse(data.data()).HasParseError())
        if (doc.HasMember("id")) {
        message.data_delete_figure.id = doc["id"].getInt();   
        }
    }     
}

void Controller::parse_game_over(std::string data){
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();
    if (!doc.Parse(data.data()).HasParseError())
        if (doc.HasMember("id")) {
        message.data_game_over.id = doc["id"].getInt();   
        }
    }     
}

void Controller::parse_timeout_move(std::string data){
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();
    if (!doc.Parse(data.data()).HasParseError())
        if (doc.HasMember("id")) {
        message.data_time_out.id = doc["id"].getInt();   
        }
        if (doc.HasMember("pos-to"))  {
            message.data_time_out.row = doc["pos-to"]["row"].getInt();
            message.data_time_out.column = doc["pos-to"]["column"].getInt() 
        }
    }     
}








