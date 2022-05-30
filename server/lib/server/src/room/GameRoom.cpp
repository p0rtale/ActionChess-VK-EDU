#include "GameRoom.hpp"

GameRoom::GameRoom(std::uint64_t id, const std::string& name, std::uint64_t maxUserNum)
    : Room(id, name, maxUserNum) {}

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

std::vector<uint64_t> GameRoom::runGame() {
    m_gameStarted = true;

    auto iterator = m_readyPlayers.begin();
    auto firstSessionId = *iterator;
    auto secondSessionId = *(++iterator);
    auto colors = m_game->init(m_sessions.at(firstSessionId), m_sessions.at(secondSessionId));

    if (colors[0] == 'w') {
        return std::vector<uint64_t>({firstSessionId, secondSessionId});
    }
    return std::vector<uint64_t>({secondSessionId, firstSessionId});
}

std::int64_t GameRoom::makeMove(const std::shared_ptr<Session>& session, std::uint64_t figureId, 
                                 std::uint64_t x, std::uint64_t y) {
    return m_game->makeMove(session.get(), figureId, x, y);
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
        return true;
    }

    return false;
}
