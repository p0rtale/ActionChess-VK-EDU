#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <queue>

#include "Request.hpp"
#include "User.hpp"

class RoomController;
class Connection;

class Session final: public std::enable_shared_from_this<Session> {
public:

    Session(std::shared_ptr<boost::asio::io_context> ioContext,
            std::shared_ptr<boost::asio::ssl::context> sslContext,
            boost::asio::ip::tcp::socket&& socket, 
            std::shared_ptr<RoomController> roomController);

    ~Session();

    void sslHandshake();

    void bindConnection();

    void write(std::string message);

    std::uint64_t createRoom(const std::string& name);

    void moveToRoom(std::uint64_t roomId);

    void moveFromRoom();

    std::vector<std::string> getAllRooms();

    void runGame();

    void broadcast(const std::string& message);

    void closeConnection();

    void handleRequests();
    
private:

    void handleRequest();

    enum class State {
        SYN,
        ACK,
        CLOSED
    };

private:

    User m_user {};

    State m_state { State::CLOSED };

    std::shared_ptr<RoomController> m_roomController { nullptr };

    std::shared_ptr<std::queue<Request>> m_requestQueue { nullptr };

    std::shared_ptr<boost::asio::io_context> m_ioContext { nullptr };

    std::shared_ptr<Connection> m_connection { nullptr };
};
