#include "Message.hpp"

#include <map>

std::string typeToStr(const RequestType type) {
    static std::map<RequestType, std::string> kMapType = {
        { RequestType::DEFAULT,        "default"       },
        { RequestType::GET_ID,         "get-id"        },
        { RequestType::CREATE_ROOM,    "create-room"   },
        { RequestType::JOIN_ROOM,      "join-room"     },
        { RequestType::USER_ENTERED,   "user-entered"  },
        { RequestType::LEAVE_ROOM,     "leave-room"    },
        { RequestType::USER_LEFT,      "user-left"     },
        { RequestType::GET_ALL_ROOMS,  "get-all-rooms" },
        { RequestType::WRITE_MESSAGE,  "write-message" },
        { RequestType::NEW_MESSAGE,    "new-message"   },
        { RequestType::READY_PLAY,     "ready-play"    },
        { RequestType::NEW_READY,      "new-ready"     },
        { RequestType::GAME_STARTED,   "game-started"  },
        { RequestType::MOVE_FIGURE,    "move-figure"   }
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
        { "new-ready",      RequestType::NEW_READY     },
        { "game-started",   RequestType::GAME_STARTED  },
        { "move-figure",    RequestType::MOVE_FIGURE   }
    };

    if (kMapStr.find(str) != kMapStr.end()) {
        return kMapStr.at(str);
    }
    return RequestType::UNDEFINED;
}
