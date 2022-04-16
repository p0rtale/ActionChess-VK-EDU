#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

#include "Session.hpp"

class Room {
public:
    Room();

    ~Room();

    void addSession(const std::shared_ptr<Session>& session);

    void removeSession(const Session* session);

    void broadcast(const std::string& message, const Session* session);

    void clear();

private:
    
    std::string m_name {};

    const std::size_t m_id { 0 };

    std::size_t m_userNum { 0 };

    std::size_t m_maxUserNum { 0 };

    std::unordered_map<std::uint64_t, std::shared_ptr<Session>> m_sessions;
};
