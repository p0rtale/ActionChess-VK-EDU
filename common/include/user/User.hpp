#pragma once

#include <cstdint>
#include <string>

class User final {
public:
    User(): m_id(s_usersNum++) {}

    ~User() = default;

    std::uint64_t m_id;
    std::string m_name;
    std::uint64_t m_roomId;

private:
    inline static std::uint64_t s_usersNum = 0; 
};
