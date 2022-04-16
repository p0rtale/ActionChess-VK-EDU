#include "Server.hpp"

#include "RoomController.hpp"

Server::Server(std::shared_ptr<boost::asio::io_context> ioContext, std::uint16_t port)
    : m_ioContext { ioContext },
      m_sslContext { std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23)  },
      m_acceptor { *m_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port) },
      m_roomController { std::make_shared<RoomController>() } {}

void Server::run() {}

void Server::shutdown() {}
