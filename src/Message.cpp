#include "Message.hpp"

#include <map>

std::string typeToStr(const RequestType type) {
    static std::map<RequestType, std::string> kMapType = {
        { RequestType::DEFAULT,        "default"       },
        { RequestType::GAME_OVER,     "game-over"    },
        { RequestType::START_GAME,     "start-game"    },
        { RequestType::MAKE_MOVE,      "make-move"     }
    };
    return kMapType.at(type);
}

RequestType strToType(const std::string& str) {
    static std::map<std::string, RequestType> kMapStr = {
        { "default",        RequestType::DEFAULT       },
        { "game-over",     RequestType::GAME_OVER    },
        { "start-game",     RequestType::START_GAME    },
        { "make-move",      RequestType::MAKE_MOVE     }
    };
    return kMapStr.at(str);
}