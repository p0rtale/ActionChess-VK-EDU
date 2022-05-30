#pragma once

#include <unordered_set>

#include "Game.hpp"
#include "Room.hpp"

class GameRoom: public Room {
public:
    GameRoom(std::uint64_t id, const std::string& name, std::uint64_t maxUserNum);

    ~GameRoom() = default;

    bool addSession(const std::shared_ptr<Session>& session) override;
    
    bool removeSession(std::uint64_t id) override;

    std::vector<uint64_t> runGame();

    std::int64_t makeMove(const std::shared_ptr<Session>& session, std::uint64_t figureId, 
                           std::uint64_t x, std::uint64_t y);

    bool gameStarted() const;

    bool setReady(std::uint64_t id);

private:
    std::shared_ptr<Game> m_game = std::make_shared<Game>();

    std::unordered_set<std::uint64_t> m_readyPlayers;  // Guarded m_readyPlayersMutex 

    std::uint64_t m_readyPlayersNum = 0;

    bool m_gameStarted = false;

    mutable std::mutex m_readyPlayersMutex;
};
