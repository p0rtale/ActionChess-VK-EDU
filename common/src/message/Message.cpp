#include "Message.hpp"

#include <map>

std::string typeToStr(const RequestType type) {
    static std::map<RequestType, std::string> kMapType = {
        { RequestType::DEFAULT,        "default"       },
        { RequestType::GET_ID,         "get-id"        },
        { RequestType::CREATE_ROOM,    "create-room"   },
        { RequestType::JOIN_ROOM,      "join-room"     },
        { RequestType::LEAVE_ROOM,     "leave-room"    },
        { RequestType::GET_ALL_ROOMS,  "get-all-rooms" },
        { RequestType::WRITE_MESSAGE,  "write-message" },
        { RequestType::READY_PLAY,     "ready-play"    },
        { RequestType::MAKE_MOVE,      "make-move"     }
    };

    if (kMapType.find(type) != kMapType.end()) {
        return kMapType.at(type);
    }
    return "undefined";
}

RequestType strToType(const std::string& str) {
    static std::map<std::string, RequestType> kMapStr = {
        { "default",        RequestType::DEFAULT       },
        { "get-id",         RequestType::GET_ID        },
        { "create-room",    RequestType::CREATE_ROOM   },
        { "join-room",      RequestType::JOIN_ROOM     },
        { "user-entered",   RequestType::USER_ENTERED  },
        { "leave-room",     RequestType::LEAVE_ROOM    },
        { "user-left",      RequestType::USER_LEFT     },
        { "get-all-rooms",  RequestType::GET_ALL_ROOMS },
        { "write-message",  RequestType::WRITE_MESSAGE },
        { "new-message",    RequestType::NEW_MESSAGE   },
        { "ready-play",     RequestType::READY_PLAY    },
        { "game-started",   RequestType::GAME_STARTED  },
        { "make-move",      RequestType::MAKE_MOVE     }
    };

    if (kMapStr.find(str) != kMapStr.end()) {
        return kMapStr.at(str);
    }
    return RequestType::UNDEFINED;
}
