#pragma once

#include <string>

const std::string kMessageSeparator = "\r\n";

enum class RequestType {
    DEFAULT,
    START_GAME,
    GAME_OVER,
    MAKE_MOVE
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