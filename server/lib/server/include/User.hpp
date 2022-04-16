#pragma once

#include <cstdint>
#include <string>

struct User final {
    User();

    std::uint64_t m_id;
    std::string m_name;
    std::uint64_t m_roomId;
};
