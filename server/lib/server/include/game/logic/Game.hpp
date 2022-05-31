#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MessageQueue.hpp"
#include "FigureHandler.hpp"
#include "Session.hpp"

struct Id_color
{
    Id_color() = default;

    void setPlayersId(std::uint64_t id1, std::uint64_t id2)
    {
        this->white_id = 0;
        this->white_id = 0;
    }
    void getId(std::uint64_t id1, std::uint64_t id2)
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

    std::uint64_t white_id;
    std::uint64_t black_id;
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
<<<<<<< HEAD:server/lib/server/include/game/logic/Game.hpp
    std::vector<char> init( const std::shared_ptr<Session>& session1,  const std::shared_ptr<Session>& session2);
=======
    vector<char> init( const std::shared_ptr<Session>& session1,  const std::shared_ptr<Session>& session2);
    bool isInGame();
    char whoWins();
>>>>>>> dev-EvilAv:interfaces/game.h
    // void addRequest(std::string request);
    // void extractData();
    // std::string sendResponse(int code);
};
