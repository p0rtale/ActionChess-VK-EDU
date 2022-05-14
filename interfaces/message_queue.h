#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H
#include <iostream>
#include <string>
#include <queue>

class MsgQueue
{
private:
    queue <std::string> data;
public:
    MsgQueue();
    ~MsgQueue();
    std::string get();
    void add(std::string msg);
};

#endif