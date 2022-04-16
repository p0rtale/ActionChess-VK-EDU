#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "Room.hpp"

class Session;

class RoomController final {
public:

    RoomController();

    ~RoomController();

    bool addSession(const std::shared_ptr<Session>& session);

    void removeSession(const std::shared_ptr<Session>& session);

    std::uint64_t createRoom(std::string name);

    void removeRoom(std::uint64_t roomId);

    void moveToRoom(std::uint64_t roomId, const std::shared_ptr<Session>& session);

    void moveFromRoom(std::uint64_t roomId, const std::shared_ptr<Session>& session);

    std::vector<std::string> getAllRooms() const;

    void runGame(std::uint64_t roomId);

    void broadcast(const std::string& message, const Session* session);

    void clear();

private:

    std::unordered_map<std::uint64_t, std::shared_ptr<Room>> m_rooms;

    std::shared_ptr<Room> m_mainRoom { nullptr };
};
