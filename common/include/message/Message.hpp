#pragma once

#include <string>

const std::string kMessageSeparator = "\r\n";

enum class RequestType {
    DEFAULT,

    GET_ID,

    CREATE_ROOM,

    JOIN_ROOM,
    USER_ENTERED,

    LEAVE_ROOM,
    USER_LEFT,

    GET_ALL_ROOMS,

    WRITE_MESSAGE,
    NEW_MESSAGE,

    READY_PLAY,
    NEW_READY,
    GAME_STARTED,

    MOVE_FIGURE,

    UNDEFINED
};

enum class ResponseStatus {
    UPDATE = 0,
    OK = 200,
    METHOD_NOT_ALLOWED = 405,
    FAILED_DEPENDENCY = 424,
    INTERNAL_SERVER_ERROR = 500,
};

std::string typeToStr(const RequestType type);
RequestType strToType(const std::string& str);

class Message {
public:
    Message() = default;

    virtual ~Message() = default;

    virtual void parseJSON(const std::string& json) = 0;

    virtual void toJSON(std::string& json) const = 0;
};
