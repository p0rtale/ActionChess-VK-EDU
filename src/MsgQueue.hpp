#pragma once

#include <queue>

#include "Request.hpp"

class RequestQueue {
public:
    RequestQueue() = default;

    ~RequestQueue() = default;

    void RequestAdd(Request&& request);

    void push(std::string&& data);

    void extractQueue(std::queue<Request>& queue_);

    void extractData(std::vector<boost::asio::const_buffer>& bufferData);

    std::size_t size();

private:
    std::queue<Request> queue; 

    std::vector<std::string> buffers;
    
    mutable std::mutex m;
};