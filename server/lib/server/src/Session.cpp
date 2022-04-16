#include "Session.hpp"

#include "Connection.hpp"

Session::Session(std::shared_ptr<boost::asio::io_context> ioContext,
                 std::shared_ptr<boost::asio::ssl::context> sslContext,
                 boost::asio::ip::tcp::socket&& socket, 
                 std::shared_ptr<RoomController> roomController)
                 : m_roomController { roomController }, 
                   m_requestQueue { std::make_shared<std::queue<Request>>() }, 
                   m_ioContext { ioContext }, 
                   m_connection { std::make_shared<Connection>(
                       ioContext.get(), 
                       sslContext.get(),
                       std::move(socket), 
                       m_requestQueue
                   )} {}

Session::~Session() {}

void Session::sslHandshake() {}

void Session::bindConnection() {}

void Session::write(std::string message) {}

std::uint64_t Session::createRoom(const std::string& name) {}

void Session::moveToRoom(std::uint64_t roomId) {}

void Session::moveFromRoom() {}

std::vector<std::string> Session::getAllRooms() {}

void Session::runGame() {}

void Session::broadcast(const std::string& message) {}

void Session::closeConnection() {}

void Session::handleRequests() {}
