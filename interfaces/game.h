#ifndef GAME_H
#define GAME_H
#include "message_queue.h"
#include <iostream>
#include <string>

class Game
{
private:
    MsgQueue requestQueue;

public:
    Game();
    ~Game();
    void addRequest(std::string request);
    void extractData();
    std::string sendResponse(int code);
};

#endif