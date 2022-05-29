#pragma once

#include <iostream>
#include <string>
#include <queue>

class MsgQueue
{
private:
    std::queue <std::string> data;
public:
    MsgQueue();
    std::string get();
    void add(std::string msg);
};
