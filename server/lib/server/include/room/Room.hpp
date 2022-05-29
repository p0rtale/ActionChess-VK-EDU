#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Session.hpp"

class Room {
public:
    Room(std::uint64_t id, const std::string& name, std::uint64_t maxUsersNum);

    ~Room();

    std::string getName() const;

    std::uint64_t getId() const;

    std::uint64_t getUsersNum() const;

    std::uint64_t getMaxUsersNum() const;

    virtual bool addSession(const std::shared_ptr<Session>& session);

    virtual bool removeSession(std::uint64_t id);

    std::vector<std::shared_ptr<Session>> getSessions() const;

    void write(const std::string& message, std::uint64_t id);

    void broadcast(const std::string& message, std::uint64_t id);

    std::string toJSON() const;

    void clear();

    static constexpr std::uint64_t s_infiniteUserNum = std::numeric_limits<std::uint64_t>::max();

protected:
    std::string m_name;

    const std::uint64_t m_id = 0;

    std::uint64_t m_maxUsersNum = 0;

    std::unordered_map<std::uint64_t, std::shared_ptr<Session>> m_sessions;  // Guarded by m_sessionsMutex 

    mutable std::mutex m_sessionsMutex;
};
