#include "Handler.hpp"

#include "Session.hpp"
#include "Room.hpp"

#include <rapidjson/allocators.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

static std::string valueToString(const rapidjson::Value& value) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    value.Accept(writer);

    return buffer.GetString();
}

static rapidjson::Value userToValue(const User& user, rapidjson::MemoryPoolAllocator<>& allocator) {
    const auto userId = user.getId();
    const auto userName = user.getName();

    rapidjson::Value value(rapidjson::kObjectType);
    value.AddMember("user", rapidjson::Value(rapidjson::kObjectType), allocator);

    value["user"].AddMember("id", userId, allocator);

    rapidjson::Value stringValue;
    stringValue.SetString(userName.data(), allocator);
    value["user"].AddMember("name", stringValue, allocator);

    return value;
}

static rapidjson::Value roomToValue(const Room& room, rapidjson::MemoryPoolAllocator<>& allocator, 
                                    bool withUsersList = true) {
    const auto roomId = room.getId();
    const auto roomName = room.getName();
    const auto usersNum = room.getUsersNum();
    const auto maxUsersNum = room.getMaxUsersNum();

    rapidjson::Value value(rapidjson::kObjectType);
    value.AddMember("room", rapidjson::Value(rapidjson::kObjectType), allocator);

    rapidjson::Value stringValue;
    stringValue.SetString(roomName.data(), allocator);
    value["room"].AddMember("name", stringValue, allocator);
    value["room"].AddMember("id", roomId, allocator);

    rapidjson::Value arrayValue(rapidjson::kArrayType);
    const auto sessions = room.getSessions();
    for (const auto& session: sessions) {
        arrayValue.PushBack(userToValue(session->getUser(), allocator), allocator);
    }
    value["room"].AddMember("users", arrayValue, allocator);

    value["room"].AddMember("users-num", usersNum, allocator);
    value["room"].AddMember("max-users-num", maxUsersNum, allocator);

    return value;
}

namespace Handlers {

    bool GetId::isValid() {
        m_response.m_type = RequestType::GET_ID;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void GetId::execute() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();

        rapidjson::Value value(rapidjson::kObjectType);
        value.AddMember("id", m_session->getUser().getId(), allocator);

        m_response.m_jsonData = valueToString(value);
    }

    bool CreateRoom::isValid() {
        m_response.m_type = RequestType::CREATE_ROOM;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (m_session->userInMainRoom()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        if (doc.Parse(m_request->m_jsonData.data()).HasParseError() ||
            !doc.HasMember("user") || 
            !doc["user"].HasMember("name") || !doc["user"]["name"].IsString() ||
            !doc.HasMember("room") ||
            !doc["room"].HasMember("name") || !doc["room"]["name"].IsString() ||
            !doc["room"].HasMember("max-users-num") || !doc["room"]["max-users-num"].IsUint64()) {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        // So far only 1vs1
        if (doc["room"]["max-users-num"] != 2) {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void CreateRoom::execute() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        doc.Parse(m_request->m_jsonData.data());

        const std::string roomName = doc["room"]["name"].GetString();
        const auto maxUsersNum = doc["room"]["max-users-num"].GetUint64();
        const auto roomId = m_session->createRoom(roomName, maxUsersNum); 
        if (m_session->moveToRoom(roomId)) {
            m_session->changeUserName(doc["user"]["name"].GetString());
            m_response.m_jsonData = valueToString(roomToValue(m_session->getRoom(), allocator));
        } else {
            m_response.m_status = ResponseStatus::INTERNAL_SERVER_ERROR;
        }
    }

    bool JoinRoom::isValid() {
        m_response.m_type = RequestType::JOIN_ROOM;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (m_session->userInMainRoom()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        if (doc.Parse(m_request->m_jsonData.data()).HasParseError() ||
            !doc.HasMember("user") || 
            !doc["user"].HasMember("name") || !doc["user"]["name"].IsString() ||
            !doc.HasMember("room") || 
            !doc["room"].HasMember("id") || !doc["room"]["id"].IsUint64()) {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void JoinRoom::execute() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        doc.Parse(m_request->m_jsonData.data());
        const auto roomId = doc["room"]["id"].GetUint64();

        if (m_session->moveToRoom(roomId)) {
            m_session->changeUserName(doc["user"]["name"].GetString());
            m_response.m_jsonData = valueToString(roomToValue(m_session->getRoom(), allocator));

            Response updateMessage;
            updateMessage.m_type = RequestType::USER_ENTERED;
            updateMessage.m_status = ResponseStatus::UPDATE;
            updateMessage.m_jsonData = valueToString(userToValue(m_session->getUser(), allocator));

            std::string json;
            updateMessage.toJSON(json);
            m_session->broadcast(json);
        } else {
            m_response.m_status = ResponseStatus::INTERNAL_SERVER_ERROR;
        }
    }

    bool LeaveRoom::isValid() {
        m_response.m_type = RequestType::LEAVE_ROOM;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (!m_session->userInMainRoom()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void LeaveRoom::execute() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();

        Response updateMessage;
        updateMessage.m_type = RequestType::USER_LEFT;
        updateMessage.m_status = ResponseStatus::UPDATE;

        rapidjson::Value value(rapidjson::kObjectType);
        value.AddMember("user", rapidjson::Value(rapidjson::kObjectType), allocator);
        value["user"].AddMember("id", m_session->getUser().getId(), allocator);

        updateMessage.m_jsonData = valueToString(value);

        std::string json;
        updateMessage.toJSON(json);
        m_session->broadcast(json);

        m_session->moveFromRoom();
    }

    bool GetAllRooms::isValid() {
        m_response.m_type = RequestType::GET_ALL_ROOMS;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (m_session->userInMainRoom()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void GetAllRooms::execute() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();

        rapidjson::Value value(rapidjson::kObjectType);
        value.AddMember("rooms", rapidjson::Value(rapidjson::kArrayType), allocator);

        rapidjson::Value arrayValue(rapidjson::kArrayType);
        const auto rooms = m_session->getAllRooms();
        for (const auto& room: rooms) {
            if (room.get() != nullptr) {
                arrayValue.PushBack(roomToValue(*room, allocator), allocator);
            }
        }

        value["rooms"] = arrayValue;

        m_response.m_jsonData = valueToString(value);
    }

    bool WriteMessage::isValid() {
        m_response.m_type = RequestType::WRITE_MESSAGE;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (!m_session->userInMainRoom()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        if (doc.Parse(m_request->m_jsonData.data()).HasParseError() ||
            !doc.HasMember("message") || !doc["message"].IsString()) {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void WriteMessage::execute() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        doc.Parse(m_request->m_jsonData.data());
        const std::string message = doc["message"].GetString();

        {
            rapidjson::Value value(rapidjson::kObjectType);

            rapidjson::Value stringValue;
            stringValue.SetString(message.data(), allocator);
            value.AddMember("message", stringValue, allocator);

            m_response.m_jsonData = valueToString(value);
        }

        Response updateMessage;
        updateMessage.m_type = RequestType::NEW_MESSAGE;
        updateMessage.m_status = ResponseStatus::UPDATE;

        rapidjson::Value value(rapidjson::kObjectType);
        value.AddMember("user", rapidjson::Value(rapidjson::kObjectType), allocator);
        value["user"].AddMember("id", m_session->getUser().getId(), allocator);
        
        rapidjson::Value stringValue;
        stringValue.SetString(message.data(), allocator);
        value.AddMember("message", stringValue, allocator);

        updateMessage.m_jsonData = valueToString(value);

        std::string json;
        updateMessage.toJSON(json);
        m_session->broadcast(json);
    }

}  // namespace Handlers
