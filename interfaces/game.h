#ifndef GAME_H
#define GAME_H
#include "message_queue.h"
#include "figure_handler.h"
#include <iostream>
#include <string>

class Game
{
private:
    MsgQueue* requestQueue;
    FigureHandler* handler;

public:
    Game();
    ~Game();
    void makeMove(char color, int id, int x, int y);
    // void addRequest(std::string request);
    // void extractData();
    // std::string sendResponse(int code);
};

#endif