#pragma once

#include <cstdint>
#include <string>

class User final {
public:
    User(): m_id(s_usersNum++) {}

    ~User() = default;

    std::uint64_t getId() const {
        return m_id;
    }
 
    std::string getName() const {
        return m_name;
    }

    void changeName(std::string name) {
        m_name = name;
    }

    std::uint64_t getRoomId() const { 
        return m_roomId;
    }

    void changeRoomId(std::uint64_t roomId) {
        m_roomId = roomId;
    }

private:
    std::uint64_t m_id;

    std::string m_name;

    std::uint64_t m_roomId;

    inline static std::uint64_t s_usersNum = 0; 
};
