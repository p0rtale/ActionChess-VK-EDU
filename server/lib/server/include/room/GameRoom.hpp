#pragma once

#include "Room.hpp"

class GameRoom: public Room {
public:
    GameRoom(std::uint64_t id, const std::string& name, std::uint64_t maxUserNum);

    ~GameRoom() = default;

    void runGame();

private:
    //std::shared_ptr<Game> m_game;
};
