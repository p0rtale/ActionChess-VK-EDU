#include "Session.hpp"

#include "Connection.hpp"
#include "Handler.hpp"
#include "RequestQueue.hpp"
#include "Room.hpp"
#include "RoomController.hpp"

Session::Session(std::shared_ptr<boost::asio::io_context> ioContext,
                 std::shared_ptr<boost::asio::ssl::context> sslContext,
                 boost::asio::ip::tcp::socket&& socket, 
                 std::shared_ptr<RoomController> roomController)
                 : m_roomController(roomController), 
                   m_requestQueue(std::make_shared<RequestQueue>()), 
                   m_ioContext(ioContext), 
                   m_connection(std::make_shared<Connection>(
                       ioContext.get(), 
                       sslContext.get(),
                       std::move(socket), 
                       m_requestQueue
                   )) {
    m_user.m_roomId = RoomController::s_mainRoomID;
}

Session::~Session() {
    if (m_connection != nullptr) {
        closeConnection();
    }
}

void Session::sslHandshake() {
    m_connection->sslHandshake();
    m_state = State::SYN;
}

void Session::bindConnection() {
    m_connection->addSession(weak_from_this());
}

void Session::acknowledge() {
    m_state = State::ACK;
}

std::uint64_t Session::getId() const {
    return m_user.m_id;
}

bool Session::isSyn() const {
    return m_state == State::SYN;
}

bool Session::isClosed() const {
    return m_state == State::CLOSED;
}

bool Session::isAcknowleged() const {
    return m_state == State::ACK;
}

const User& Session::getUser() const {
    return m_user;
}

const Room& Session::getRoom() const {
    return m_roomController->getRoom(m_user.m_roomId);
}

std::vector<std::shared_ptr<Room>> Session::getAllRooms() const {
    return m_roomController->getAllRooms();
}

void Session::changeUserName(std::string name) {
    m_user.m_name = std::move(name);
}

bool Session::userInMainRoom() const {
    return m_user.m_roomId == RoomController::s_mainRoomID;
}

void Session::write(std::string message) {
    m_connection->write(std::move(message));
}

std::uint64_t Session::createRoom(const std::string& name, std::size_t maxUserNum) {
    return m_roomController->createRoom(name, maxUserNum);
}

bool Session::moveToRoom(std::uint64_t roomId) {
    if (m_roomController->moveToRoom(roomId, shared_from_this())) {
        m_user.m_roomId = roomId;
        return true;
    }
    return false;
}

bool Session::moveFromRoom() {
    if (m_user.m_roomId != RoomController::s_mainRoomID) {
        m_roomController->moveFromRoom(m_user.m_roomId, shared_from_this());
        m_user.m_roomId = RoomController::s_mainRoomID;
        return true;
    }
    return false;
}

bool Session::runGame() {
    if (m_user.m_roomId != RoomController::s_mainRoomID) {
        m_roomController->runGame(m_user.m_roomId);
        return true;
    }
    return false;
}

void Session::broadcast(const std::string& message) {
    m_roomController->broadcast(message, getId());
}

void Session::removeFromRoomController() {
    if (m_user.m_roomId != RoomController::s_mainRoomID) {
        m_roomController->removeSession(shared_from_this());
    }
    m_state = State::CLOSED;    
}

void Session::closeConnection() {
    m_connection->close();
}

void Session::handleRequests() {
    boost::asio::post(*m_ioContext, [session = shared_from_this()]() {
        std::queue<Request> queue;
        session->m_requestQueue->popAll(queue);
        while (!queue.empty()) {
            session->handleRequest(std::move(queue.front()));
            queue.pop();
        }
    });    
}

void Session::handleRequest(Request&& request) {
    using namespace Handlers;

    switch (request.m_type) {
        case RequestType::CREATE_ROOM:
            createHandler<RequestType::CREATE_ROOM>(&request, this)->run();
            break;
        case RequestType::JOIN_ROOM:
            createHandler<RequestType::JOIN_ROOM>(&request, this)->run();
            break;
        case RequestType::LEAVE_ROOM:
            createHandler<RequestType::LEAVE_ROOM>(&request, this)->run();
            break;
        case RequestType::GET_ALL_ROOMS:
            createHandler<RequestType::GET_ALL_ROOMS>(&request, this)->run();
            break;
        case RequestType::WRITE_MESSAGE:
            createHandler<RequestType::WRITE_MESSAGE>(&request, this)->run();
            break;
        case RequestType::START_GAME:
            createHandler<RequestType::START_GAME>(&request, this)->run();
            break;
        case RequestType::MAKE_MOVE:
            createHandler<RequestType::MAKE_MOVE>(&request, this)->run();
            break;
    }
}
