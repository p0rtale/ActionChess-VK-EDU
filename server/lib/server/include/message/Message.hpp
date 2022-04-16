#pragma once

#include <string>

enum class RequestType {
    ERROR,

    CREATE_ROOM,
    JOIN_ROOM,
    LEAVE_ROOM,
    GET_ALL_ROOMS,

    WRITE_MESSAGE,

    START_GAME,
    MAKE_MOVE
};

struct Message {
    virtual ~Message() = default;

    virtual void parseJSON(const std::string& json) = 0;

    virtual void toJSON(std::string& json) const = 0;
};
