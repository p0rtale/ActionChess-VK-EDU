#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <queue>

#include "Request.hpp"

class Session;

class Connection final: public std::enable_shared_from_this<Connection> {
public:
    Connection(boost::asio::io_context* ioContext, 
               boost::asio::ssl::context* sslContext,
               boost::asio::ip::tcp::socket&& socket,
               std::shared_ptr<std::queue<Request>> requestQueue);

    void sslHandshake();

    void read();

    void write(std::string&& message);

    void close();

private:

    enum class State {
        DEFAULT,
        WRITING,
        CLOSED
    };

    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> m_socket;

    boost::asio::io_context::strand m_strand;

    std::shared_ptr<std::queue<Request>> m_requestQueue { nullptr };

    std::weak_ptr<Session> m_bindedSession {};

    boost::asio::streambuf m_readBuf;
    std::vector<boost::asio::const_buffer> m_writeBuf;
};
