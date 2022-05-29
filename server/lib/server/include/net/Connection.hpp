#pragma once

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <optional>

#include "Logger.hpp"
#include "WriteBufferSequence.hpp"

class RequestQueue;
class Session;

class Connection final: public std::enable_shared_from_this<Connection> {
public:
    Connection(boost::asio::io_context* ioContext, 
               boost::asio::ssl::context* sslContext,
               boost::asio::ip::tcp::socket&& socket,
               std::uint64_t id,
               std::shared_ptr<RequestQueue> requestQueue);

    ~Connection();

    void addSession(std::weak_ptr<Session> session);

    void sslHandshake();

    void read();

    void write(std::string&& message);

    void close();

private:
    void write();

    void readHandler(const boost::system::error_code& error, std::size_t transferredBytes);

    void writeHandler(const boost::system::error_code& error, std::size_t transferredBytes);

    void publishRequest();

private:
    enum class State {
        DEFAULT,
        WRITING,
        CLOSED
    };

    State m_state = State::DEFAULT;

    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> m_socket;

    boost::asio::io_context::strand m_strand;

    std::shared_ptr<RequestQueue> m_requestQueue;

    std::weak_ptr<Session> m_bindedSession;

    std::optional<Logger> m_logger;

    const std::uint64_t m_id = 0;

    boost::asio::streambuf m_readBuf;
    WriteBufferSequence m_writeBuf;
};
