#pragma once
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include "Client.hpp"

struct listen_move{
    int id = -1;
    unsigned int row = 0;
    unsigned int column = 0;
    int time = 0;
    void del(){
        id = -1;
        row = 0;
        column = 0;
        time = 0
    }
    listen_move(const listen_move& r){
        id = r.id;
        row = r.row;
        column = r.column;
        time  = r.time;
    }
};

struct delete_figure{
    int id = -1;
    void del(){
        id = -1;
    }
    delete_figuree(const delete_figure& r){
        id = r.id;
    }
};

struct game_over{
    int id = -1;
    void del(){
        id = -1;
    }
    delete_figuree(const delete_figure& r){
        id = r.id;
    }

};

struct time_out{
    int id = -1;
    unsigned int row = 0;
    unsigned int column = 0;
    void del(){
        id = -1;
        row = 0;
        column = 0;
    }
    time_out(const time_out& r){
        id = r.id;
        row = r.row;
        column = r.column;
    }
};
struct Message
{
    std::string type;
    listen_move data_listen_move;
    delete_figure data_delete_figure;
    game_over data_game_over;
    time_out data_time_out;
};

struct Tile 
{
    unsigned int row = 0;
    unsigned int column = 0;

    Tile(){
        row = 0;
        column = 0;
    }

    Tile (const Tile& other)
    {
        this->row = other.row;
        this->column = other.column;
    }

    Tile(unsigned int row_, unsigned int column_){
        row = row_;
        column = column_;
    }
};

class Controller {
public:
    void send_message_move(int id, Tile pos_to);
    void tick();

private:
    void parse_listen_move(std::string data);
    void parse_delete_figure(std::string data);
    void parse_timeout_move(std::string data);
    void parse_game_over(std::string data);
    Client c;
    Message message;
};