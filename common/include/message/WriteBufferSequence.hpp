#pragma once

class WriteBufferSequence {
public:
    WriteBufferSequence() = default;
    
    ~WriteBufferSequence() = default;

    void push(std::string&& data) {
        m_buffers.emplace_back(std::move(data));
    }

    void popAll(std::vector<boost::asio::const_buffer>& bufferSequence) {
        for (const auto& string: m_buffers) {
            bufferSequence.emplace_back(boost::asio::const_buffer(string.data(), string.size()));
        }
        m_buffers.clear();
    }

    std::size_t size() const {
        return m_buffers.size();
    }

private:
    std::vector<std::string> m_buffers;
};
