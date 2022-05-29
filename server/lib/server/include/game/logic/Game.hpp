#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MessageQueue.hpp"
#include "FigureHandler.hpp"
#include "Session.hpp"

struct Id_color
{
    std::uint16_t white_id;
    std::uint16_t black_id;
<<<<<<< HEAD:server/lib/server/include/game/logic/Game.hpp

    Id_color() = default;

    void setPlayersId(std::uint64_t id1, std::uint64_t id2)
=======
    Id_color(std::uint64_t id1, std::uint64_t id2)
>>>>>>> 097f616e05b83ff425765b75027edbaf557909cd:interfaces/game.h
    {
        this->white_id = id1;
        this->black_id = id2;
    }

    char getColor(std::uint64_t ses)
    {
        if (this->white_id == ses)
            return 'w';
        else if (this->black_id == ses)
            return 'b';
        else
            return NULL;
    }
};


class Game
{
private:
    MsgQueue* requestQueue;
    FigureHandler* handler;
    Id_color colors;

public:
    Game();
    ~Game();
    int makeMove(const Session* ses, int id, int x, int y);
    std::vector<char> init( const std::shared_ptr<Session>& session1,  const std::shared_ptr<Session>& session2);
    // void addRequest(std::string request);
    // void extractData();
    // std::string sendResponse(int code);
};
