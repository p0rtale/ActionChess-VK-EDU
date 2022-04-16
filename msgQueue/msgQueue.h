
#pragma once
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
