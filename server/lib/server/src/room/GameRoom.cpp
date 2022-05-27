#include "GameRoom.hpp"

GameRoom::GameRoom(std::uint64_t id, const std::string& name, std::uint64_t maxUserNum): Room(id, name, maxUserNum) {}

bool GameRoom::addSession(const std::shared_ptr<Session>& session) {
    const auto id = session->getUser().getId();
    auto userNum = getUsersNum();

    if (userNum >= m_maxUsersNum) {
        return false;
    }

    std::lock_guard<std::mutex> guard(m_mutex);
    m_sessions.emplace(id, session);

    if (getUsersNum() == m_maxUsersNum) {
        runGame();
    }

    return true;
}

void GameRoom::runGame() {}
