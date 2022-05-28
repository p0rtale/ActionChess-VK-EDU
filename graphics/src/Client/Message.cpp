#include "Message.hpp"

#include <map>

std::string typeToStr(const RequestType type) {
    static std::map<RequestType, std::string> kMapType = {
        { RequestType::DEFAULT,        "default"       },
        { RequestType::CREATE_ROOM,    "create-room"   },
        { RequestType::JOIN_ROOM,      "join-room"     },
        { RequestType::LEAVE_ROOM,     "leave-room"    },
        { RequestType::GET_ALL_ROOMS,  "get-all-rooms" },
        { RequestType::WRITE_MESSAGE,  "write-message" },
        { RequestType::START_GAME,     "start-game"    },
        { RequestType::MAKE_MOVE,      "make-move"     }
    };
    return kMapType.at(type);
}

RequestType strToType(const std::string& str) {
    static std::map<std::string, RequestType> kMapStr = {
        { "default",        RequestType::DEFAULT       },
        { "create-room",    RequestType::CREATE_ROOM   },
        { "join-room",      RequestType::JOIN_ROOM     },
        { "leave-room",     RequestType::LEAVE_ROOM    },
        { "user-left",      RequestType::USER_LEFT     },
        { "get-all-rooms",  RequestType::GET_ALL_ROOMS },
        { "write-message",  RequestType::WRITE_MESSAGE },
        { "new-message",    RequestType::NEW_MESSAGE   },
        { "start-game",     RequestType::START_GAME    },
        { "game-started",   RequestType::GAME_STARTED  },
        { "make-move",      RequestType::MAKE_MOVE     }
    };
    return kMapStr.at(str);
}
