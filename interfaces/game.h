#ifndef GAME_H
#define GAME_H
#include "message_queue.h"
#include "figure_handler.h"
#include <iostream>
#include <string>
#include <vector>

struct Id_color
{
    std::uint16_t white_id;
    std::uint16_t black_id;
    Id_color(std::uint64_t id1, std::uint64_t id2)
    {
        this->white_id = 0;
        this->white_id = 0;
    }
    void getId(std::uint64_t id1, std::uint64_t id2)
    {
        this->white_id = id1;
        this->white_id = id2;
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
    vector<char> init( const std::shared_ptr<Session>& session1,  const std::shared_ptr<Session>& session2);
    bool isInGame();
    char whoWins();
    // void addRequest(std::string request);
    // void extractData();
    // std::string sendResponse(int code);
};

#endif