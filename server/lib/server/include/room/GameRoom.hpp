#pragma once

#include "Room.hpp"

class GameRoom: public Room {
public:
    GameRoom();

    ~GameRoom();

    void runGame();

private:
    std::shared_ptr<Game> m_game;
};
