#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H
#include <iostream>
#include <string>

class MsgQueue
{
private:
    int bufferSize;
    int dataSize;
    std::string* data;
public:
    MsgQueue();
    ~MsgQueue();
    std::string get();
    void add();
};

#endif