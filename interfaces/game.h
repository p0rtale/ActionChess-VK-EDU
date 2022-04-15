#ifndef GAME_H
#define GAME_H
#include "message_queue.h"
#include <iostream>
#include <string>

class game
{
private:
    MsgQueue requestQueue;

public:
    game();
    ~game();
    void addRequest(std::string request);
    void extractData();
    std::string sendResponse();
};

#endif