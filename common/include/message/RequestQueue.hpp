#pragma once

#include <queue>

#include "Request.hpp"

class RequestQueue {
public:
    RequestQueue() = default;

    ~RequestQueue() = default;

    void push(Request&& request) {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_queue.emplace(std::move(request));
    }

    void popAll(std::queue<Request>& queue) {
        std::lock_guard<std::mutex> guard(m_mutex);
        while (!m_queue.empty()) {
            queue.push(m_queue.front());
            m_queue.pop();
        }
    }

private:
    std::queue<Request> m_queue;  // Guarded by m_mutex 

    mutable std::mutex m_mutex;
};
