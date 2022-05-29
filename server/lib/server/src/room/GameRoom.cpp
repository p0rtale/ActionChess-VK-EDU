#include "GameRoom.hpp"

GameRoom::GameRoom(std::uint64_t id, const std::string& name, std::uint64_t maxUserNum): Room(id, name, maxUserNum) {}

bool GameRoom::addSession(const std::shared_ptr<Session>& session) {
    const auto id = session->getUser().getId();
    auto userNum = getUsersNum();

    if (userNum >= m_maxUsersNum) {
        return false;
    }

    std::lock_guard<std::mutex> guard(m_sessionsMutex);
    m_sessions.emplace(id, session);

    return true;
}

bool GameRoom::removeSession(std::uint64_t id) {
    {
        std::lock_guard<std::mutex> guard(m_readyPlayersMutex);

        if (m_readyPlayers.find(id) != m_readyPlayers.end()) {
            m_readyPlayers.erase(id);
            m_readyPlayersNum--;
        }
    }

    std::lock_guard<std::mutex> guard(m_sessionsMutex);

    if (m_sessions.erase(id)) {
        return true;
    }

    return false;    
}

void GameRoom::runGame() {
    m_gameStarted = true;
}

bool GameRoom::gameStarted() const {
    return m_gameStarted;
}

bool GameRoom::setReady(std::uint64_t id) {
    std::lock_guard<std::mutex> guard(m_readyPlayersMutex);

    if (m_readyPlayers.find(id) == m_readyPlayers.end()) {
        m_readyPlayers.insert(id);
        m_readyPlayersNum++;
    }

    if (m_readyPlayersNum == m_maxUsersNum) {
        runGame();
        return true;
    }

    return false;
}
