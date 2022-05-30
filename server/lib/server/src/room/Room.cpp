#include "Room.hpp"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

Room::Room(std::uint64_t id, const std::string& name, std::uint64_t maxUsersNum)
    : m_id(id), m_name(name), m_maxUsersNum(maxUsersNum) {}

Room::~Room() {
    clear();
}

std::string Room::getName() const {
    return m_name;
}

std::uint64_t Room::getId() const {
    return m_id;
}

std::uint64_t Room::getUsersNum() const {
    return m_sessions.size();
}

std::uint64_t Room::getMaxUsersNum() const {
    return m_maxUsersNum;
}

bool Room::addSession(const std::shared_ptr<Session>& session) {
    std::lock_guard<std::mutex> guard(m_sessionsMutex);

    const auto id = session->getUser().getId();
    auto userNum = getUsersNum();

    if (userNum >= m_maxUsersNum) {
        return false;
    }

    m_sessions.emplace(id, session);

    return true;
}

bool Room::removeSession(std::uint64_t id) {
    std::lock_guard<std::mutex> guard(m_sessionsMutex);

    if (m_sessions.erase(id)) {
        return true;
    }

    return false;    
}

std::shared_ptr<Session> Room::getSession(std::uint64_t id) const {
    std::lock_guard<std::mutex> guard(m_sessionsMutex);

    auto iterator = m_sessions.find(id);
    if (iterator != m_sessions.end()) {
        auto session = iterator->second;
        return session;
    }

    return nullptr;
}

std::vector<std::shared_ptr<Session>> Room::getSessions() const {
    std::vector<std::shared_ptr<Session>> sessions;

    std::lock_guard<std::mutex> guard(m_sessionsMutex);
    for (const auto& pair: m_sessions) {
        const auto session = pair.second;
        sessions.emplace_back(session);
    }

    return sessions;
}

void Room::write(const std::string& message, std::uint64_t id) {
    std::lock_guard<std::mutex> guard(m_sessionsMutex);

    auto iterator = m_sessions.find(id);
    if (iterator != m_sessions.end()) {
        auto session = iterator->second;
        session->write(message);
    }
}

void Room::broadcast(const std::string& message, std::uint64_t id) {
    std::lock_guard<std::mutex> guard(m_sessionsMutex);

    for (auto& pair: m_sessions) {
        auto session = pair.second;
        const auto currentId = session->getUser().getId();
        if (currentId != id) {
            session->write(message);
        }
    }
}

std::string Room::toJSON() const {
    rapidjson::Document doc;
    doc.SetObject();
    auto& allocator = doc.GetAllocator();

    rapidjson::Value value;
    value.SetString(m_name.data(), allocator);
    doc.AddMember("name", value, allocator);

    doc.AddMember("id", m_id, allocator);

    //rapidjson::Value arrayValue(rapidjson::kArrayType);
    //doc.AddMember("users", arrayValue, allocator);

    doc.AddMember("users-num", getUsersNum(), allocator);
    doc.AddMember("max-users-num", getMaxUsersNum(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

void Room::clear() {
    std::lock_guard<std::mutex> guard(m_sessionsMutex);
    m_sessions.clear();    
}
