#include "Game.hpp"

#include <vector>

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
    int Game::makeMove(const Session* ses, int id, int x, int y)
    {
        char temp = colors.getColor(ses->getId());
        if (temp == NULL)
            return -1;
        int timer = this->handler->moveFigure(id, Tile(x, y));
        if (this->handler->getWinner() != 'n')
            std::cout<<"Winner is "<<this->handler->getWinner()<<std::endl;
        return timer;
    }
    std::vector<char> Game::init( const std::shared_ptr<Session>& session1,  const std::shared_ptr<Session>& session2)
    {
<<<<<<< HEAD:server/lib/server/src/game/logic/Game.cpp
        colors.setPlayersId(session1->getId(), session2->getId());
        std::vector<char> res;
        res.push_back('w');
        res.push_back('b');
=======
        this->colors.getId(session1->getId(), session2->getId());
        vector<char> res;
        res.push_back("w");
        res.push_back("b");
>>>>>>> dev-EvilAv:logic/Game.cpp
        return res;
    }
    bool Game::isInGame()
    {
        if (this->handler->getWinner() == 'n')
            return true;
        else
            return false;
    }
    char Game::whoWins()
    {
        return this->handler->getWinner();
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