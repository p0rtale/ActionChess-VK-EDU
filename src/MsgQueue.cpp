#include "MsgQueue.hpp"

void MsgQueue::RequestAdd(Request&& request) {
        m.lock();
        queue.emplace(std::move(request));
        m.unlock();
}

void MsgQueue::push(std::string&& data) {
        buffers.emplace_back(std::move(data));
}

void MsgQueue::extractQueue(std::queue<Request>& queue_) {
        m.lock();;
        while (!queue.empty()) {
            queue_.push(queue.front());
            queue.pop();
        }
        m.unlock();
}

void MsgQueue::extractData(std::vector<boost::asio::const_buffer>& bufferData) {
        for (const auto& string: buffers) {
            bufferData.emplace_back(boost::asio::const_buffer(string.data(), string.size()));
        }
        buffers.clear();
}

std::size_t MsgQueue::size() const {
    return m_buffers.size();
}