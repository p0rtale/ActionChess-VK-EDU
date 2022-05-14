#include "../interfaces/message_queue.h"


using namespace std;

class MsgQueue
{
private:
    queue<std::string> data;
public:
    MsgQueue(){}
    ~MsgQueue(){}
    string get()
    {
        if (data.empty())
            return NULL;
        string temp = data.front();
        data.pop();
        return temp;
    }
    void add(string msg)
    {
        data.push(msg);
    }
};