#pragma once

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "Request.hpp"
#include "User.hpp"

class Connection;
class GameRoom;
class RequestQueue;
class Room;
class RoomController;

class Session final: public std::enable_shared_from_this<Session> {
public:
    Session(std::shared_ptr<boost::asio::io_context> ioContext,
            std::shared_ptr<boost::asio::ssl::context> sslContext,
            boost::asio::ip::tcp::socket&& socket, 
            std::shared_ptr<RoomController> roomController);

    ~Session();

    void sslHandshake();

    void bindConnection();

    void acknowledge();

    std::uint64_t getId() const;

    bool isSyn() const;

    bool isClosed() const;

    bool isAcknowleged() const;

    const User& getUser() const;

    const Room& getRoom() const;

    const GameRoom& getGameRoom() const;

    std::vector<std::shared_ptr<Room>> getAllRooms() const;

    void changeUserName(std::string name);

    bool userInMainRoom() const;

    void handleRequests();

    void write(std::string message);

    std::uint64_t createRoom(const std::string& name, std::size_t maxUserNum);

    bool moveToRoom(std::uint64_t roomId);

    bool moveFromRoom();

    bool setReadyToPlay();

    bool runGame();

    std::uint64_t makeMove(std::uint64_t figureId, std::uint64_t x, std::uint64_t y);

    void broadcast(const std::string& message);

    void removeFromRoomController();

    void closeConnection();

private:
    void handleRequest(Request&& request);

    enum class State {
        SYN,
        ACK,
        CLOSED
    };

private:
    User m_user;

    State m_state = State::CLOSED;

    std::shared_ptr<RoomController> m_roomController;

    std::shared_ptr<RequestQueue> m_requestQueue;

    std::shared_ptr<boost::asio::io_context> m_ioContext;

    std::shared_ptr<Connection> m_connection;
};
