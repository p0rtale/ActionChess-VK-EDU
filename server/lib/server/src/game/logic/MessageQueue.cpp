#include "MessageQueue.hpp"

using namespace std;
    MsgQueue::MsgQueue()
    {
        queue <std::string> data;
    }
    string MsgQueue::get()
    {
        if (data.empty())
            return NULL;
        string temp = data.front();
        data.pop();
        return temp;
    }
    void MsgQueue::add(string msg)
    {
        data.push(msg);
    }
