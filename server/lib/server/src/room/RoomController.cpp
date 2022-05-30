#include "RoomController.hpp"

RoomController::RoomController() {
    m_rooms.emplace(s_unusedGameRoomID, nullptr);
}

RoomController::~RoomController() {
    clear();
}

bool RoomController::addSession(const std::shared_ptr<Session>& session) {
    return m_mainRoom->addSession(session);
}

void RoomController::removeSession(const std::shared_ptr<Session>& session) {
    const auto userId = session->getUser().getId();
    if (!m_mainRoom->removeSession(userId)) {
        const auto roomId = session->getUser().getRoomId();

        std::lock_guard<std::mutex> guard(m_mutex);
        const auto it = m_rooms.find(roomId);
        if (it != m_rooms.end()) {
            auto room = it->second;
            room->removeSession(userId);
        }
    }
}

std::uint64_t RoomController::createRoom(std::string name, std::uint64_t maxUserNum) {
    std::lock_guard<std::mutex> guard(m_mutex);

    const std::uint64_t id = m_rooms.size();
    auto room = std::make_shared<GameRoom>(id, name, maxUserNum);

    m_rooms.emplace(id, std::move(room));

    return id;
}

void RoomController::removeRoom(std::uint64_t roomId) {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_rooms.erase(roomId);
}

bool RoomController::moveToRoom(std::uint64_t roomId, const std::shared_ptr<Session>& session) {
    const auto userId = session->getUser().getId();
    m_mainRoom->removeSession(userId);
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        const auto it = m_rooms.find(roomId);
        if (it != m_rooms.end()) {
            auto room = it->second;
            if (room->addSession(session)) {
                return true;
            }
        }
    }
    m_mainRoom->addSession(session);

    return false;
}

bool RoomController::moveFromRoom(std::uint64_t roomId, const std::shared_ptr<Session>& session) {
    if (roomId == s_mainRoomID) {
        return false;
    }

    std::shared_ptr<Room> room;
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        auto it = m_rooms.find(roomId);
        if (it != m_rooms.end()) {
            room = it->second;
        } else {
            return false;
        }
    }

    const auto userId = session->getUser().getId();
    if (room->removeSession(userId)) {
        m_mainRoom->addSession(session);   
    }

    if (room->getUsersNum() == 0) {
        removeRoom(roomId);
    }

    return true;
}

const Room& RoomController::getRoom(std::uint64_t id) const {
    std::lock_guard<std::mutex> guard(m_mutex);

    const auto it = m_rooms.find(id);
    if (it != m_rooms.end()) {
        auto room = it->second;
        return *room;
    }

    return *m_mainRoom;
}

const GameRoom& RoomController::getGameRoom(std::uint64_t id) const {
    std::lock_guard<std::mutex> guard(m_mutex);

    const auto it = m_rooms.find(id);
    if (it != m_rooms.end()) {
        auto room = it->second;
        return *room;
    }

    return *m_rooms.at(s_unusedGameRoomID);
}

std::string RoomController::getRoomJSON(std::uint64_t id) const {
    std::lock_guard<std::mutex> guard(m_mutex);
    
    const auto it = m_rooms.find(id);
    if (it != m_rooms.end()) {
        auto room = it->second;
        return room->toJSON();
    }

    return std::string();
}

std::vector<std::shared_ptr<Room>> RoomController::getAllRooms() const {
    std::vector<std::shared_ptr<Room>> rooms;
    
    std::lock_guard<std::mutex> guard(m_mutex);
    for (const auto& pair: m_rooms) {
        const auto room = pair.second;
        rooms.emplace_back(room);
    }

    return rooms;
}

std::vector<std::string> RoomController::getAllRoomsJSON() const {
    std::vector<std::string> rooms;
    
    std::lock_guard<std::mutex> guard(m_mutex);
    for (const auto& pair: m_rooms) {
        const auto room = pair.second;
        rooms.emplace_back(room->toJSON());
    }

    return rooms;
}

std::vector<uint64_t> RoomController::runGame(std::uint64_t id) {
    if (id == s_mainRoomID) {
        return std::vector<uint64_t>();
    }

    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_rooms.find(id);
    if (it != m_rooms.end()) {
        auto room = it->second;
        return room->runGame();
    }

    return std::vector<uint64_t>();
}

std::int64_t RoomController::makeMove(const std::shared_ptr<Session>& session, std::uint64_t figureId, 
                                       std::uint64_t x, std::uint64_t y) {
    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_rooms.find(session->getUser().getRoomId());
    if (it != m_rooms.end()) {
        auto room = it->second;
        return room->makeMove(session, figureId, x, y);
    }
}

bool RoomController::setReadyToPlay(std::uint64_t roomId, std::uint64_t playerId) {
    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_rooms.find(roomId);
    if (it != m_rooms.end()) {
        auto room = it->second;
        return room->setReady(playerId);
    }
    return false;
}

void RoomController::write(const std::string& message, std::uint64_t id) {
    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_rooms.find(id);
    if (it != m_rooms.end()) {
        auto room = it->second;
        room->write(message, id);
    }
}

void RoomController::broadcast(const std::string& message, std::uint64_t roomId, std::uint64_t userId) {
    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_rooms.find(roomId);
    if (it != m_rooms.end()) {
        auto room = it->second;
        room->broadcast(message, userId);
    }
}

void RoomController::clear() {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_rooms.clear();
    m_mainRoom->clear();
}
