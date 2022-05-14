#pragma once

#include "Room.hpp"

class GameRoom: public Room {
public:
    GameRoom(std::uint64_t id, const std::string& name, std::uint64_t maxUserNum);

    ~GameRoom() = default;

    bool addSession(const std::shared_ptr<Session>& session) override;

    void runGame();

private:
    //std::shared_ptr<Game> m_game;
};
