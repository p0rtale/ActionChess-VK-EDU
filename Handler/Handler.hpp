#pragma once
#include "msg_queue.h"
#include <iostream>
#include <string>

class handler
{
private:
    MsgQueue requestQueue;

public:
    handler();
    ~handler();
    void addRequest(std::string request);
    void extractData();
    std::string sendResponse();
};
