#pragma once

#include <memory>
#include <optional>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

class RoomController; 

class Server final {
public:
    Server(std::shared_ptr<boost::asio::io_context> ioContext, std::uint16_t port);

    ~Server();

    void run();

    void shutdown();

private:

    void setupSSLContext();

    std::string passwordCallback(std::size_t maxSize,
                                 boost::asio::ssl::context::password_purpose purpose) const;

    std::shared_ptr<boost::asio::io_context> m_ioContext;
    
    std::shared_ptr<boost::asio::ssl::context> m_sslContext;

    boost::asio::ip::tcp::acceptor m_acceptor;

    std::optional<boost::asio::ip::tcp::socket> m_socket;

    std::shared_ptr<RoomController> m_roomController;
};
