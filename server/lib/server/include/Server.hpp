#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

class RoomController; 

class Server final {
public:
    Server(std::shared_ptr<boost::asio::io_context> ioContext, std::uint16_t port);

    void run();

    void shutdown();

private:

    std::shared_ptr<boost::asio::io_context> m_ioContext;
    
    std::shared_ptr<boost::asio::ssl::context> m_sslContext;

    boost::asio::ip::tcp::acceptor m_acceptor;

    std::optional<boost::asio::ip::tcp::socket> m_socket;

    std::shared_ptr<RoomController> m_roomController { nullptr };
};
