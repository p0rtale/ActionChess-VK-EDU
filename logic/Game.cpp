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
            string delimeter = ",";
            int position = 0;
            string temp;
            string key[3] = {"\"figure\":","\"start\":", "\"end\":"}
            for (int i = 0; i < 3; i++)
            {
                position = msg.find(delimeter);
                temp = msg.substr(msq.find(key[i]), position);
                int figure_id = stoi(temp);
                msg.erase(0, pos + delimeter.length());
            }

            handler.moveFigure(figure_id, start_tile, end_tile);
        }
        catch (invalid_argument)
        {
            this->sendResponse(400);
        }
    }
    string sendResponse(int code);
};