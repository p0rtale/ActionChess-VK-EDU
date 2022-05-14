#include "../interfaces/game.h"

using namespace std;

class Game
{
private:
    MsgQueue requestQueue;
    FigureHandler handler;

public:
    Game();
    ~Game();
    void addRequest(string request)
    void extractData();
    {
        string msg = this->requestQueue.get();
        try 
        {
            int figure_id = stoi(temp.find("figure"));
            int start_tile = stoi(temp.find("start"));
            int end_tile = stoi(temp.find("end"));
            handler.moveFigure(figure_id, start_tile, end_tile);
        }
        catch (invalid_argument)
        {
            this->sendResponse(400);
        }
    }
    string sendResponse(int code);
};