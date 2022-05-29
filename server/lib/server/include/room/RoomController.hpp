#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "GameRoom.hpp"
#include "Room.hpp"

class Session;

class RoomController final {
public:
    RoomController();

    ~RoomController();

    bool addSession(const std::shared_ptr<Session>& session);

    void removeSession(const std::shared_ptr<Session>& session);

    std::uint64_t createRoom(std::string name, std::uint64_t maxUserNum);

    void removeRoom(std::uint64_t roomId);

    bool moveToRoom(std::uint64_t roomId, const std::shared_ptr<Session>& session);

    void moveFromRoom(std::uint64_t roomId, const std::shared_ptr<Session>& session);

    const Room& getRoom(std::uint64_t id) const;

    const GameRoom& getGameRoom(std::uint64_t id) const;

    std::string getRoomJSON(std::uint64_t id) const;

    std::vector<std::shared_ptr<Room>> getAllRooms() const;

    std::vector<std::string> getAllRoomsJSON() const;

    void runGame(std::uint64_t id);

    void setReadyToPlay(std::uint64_t roomId, std::uint64_t playerId);

    void write(const std::string& message, std::uint64_t id);

    void broadcast(const std::string& message, std::uint64_t roomId, std::uint64_t userId);

    void clear();

    static constexpr std::uint64_t s_mainRoomID = 0;

    static constexpr std::uint64_t s_unusedGameRoomID = 0;

private:
    std::unordered_map<std::uint64_t, std::shared_ptr<GameRoom>> m_rooms;  // Guarded by m_mutex 

    std::shared_ptr<Room> m_mainRoom = std::make_shared<Room>(s_mainRoomID, "MainRoom", Room::s_infiniteUserNum);

    mutable std::mutex m_mutex;
};
