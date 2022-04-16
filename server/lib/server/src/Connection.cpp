#include "Connection.hpp"

Connection::Connection(boost::asio::io_context* ioContext, 
                       boost::asio::ssl::context* sslContext,
                       boost::asio::ip::tcp::socket&& socket,
                       std::shared_ptr<std::queue<Request>> requestQueue)
                       : m_socket { std::move(socket), *sslContext },  
                         m_strand { *ioContext }, 
                         m_requestQueue { requestQueue } {}

void Connection::sslHandshake() {}

void Connection::read() {}

void Connection::write(std::string&& message) {}

void Connection::close() {}
