#include "game.h"

using namespace std;

    Game::Game()
    {
        this->handler = new FigureHandler();
        this->requestQueue = new MsgQueue();
    }
    Game::~Game()
    {
        delete handler;
        delete requestQueue;
    }
    void Game::makeMove(char color, int id, int x, int y)
    {
        if (id >=16 && color =='w')
            return;
        this->handler->moveFigure(id, Tile(x, y));
        if (this->handler->getWinner() != 'n')
            cout<<"Winner is "<<this->handler->getWinner()<<endl;
    }
    // void addRequest(string request)
    // void extractData();
    // {
    //     string msg = this->requestQueue.get();
    //     try 
    //     {
    //         string delimeter = ",";
    //         int position = 0;
    //         string temp;
    //         string key[3] = {"\"figure\":","\"start\":", "\"end\":"}
    //         for (int i = 0; i < 3; i++)
    //         {
    //             position = msg.find(delimeter);
    //             temp = msg.substr(msq.find(key[i]), position);
    //             int figure_id = stoi(temp);
    //             msg.erase(0, pos + delimeter.length());
    //         }

    //         handler.moveFigure(figure_id, start_tile, end_tile);
    //     }
    //     catch (invalid_argument)
    //     {
    //         this->sendResponse(400);
    //     }
    // }
    //string sendResponse(int code);