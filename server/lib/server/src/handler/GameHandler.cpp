#include "Handler.hpp"

#include "GameRoom.hpp"
#include "Session.hpp"

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

namespace Handlers {

    bool ReadyPlay::isValid() {
        m_response.m_type = RequestType::READY_PLAY;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (!m_session->userInMainRoom() && !m_session->getGameRoom().gameStarted()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void ReadyPlay::execute() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();

        if (m_session->setReadyToPlay()) {
            std::string json;

            Response updateMessage;
            updateMessage.m_type = RequestType::GAME_STARTED;
            updateMessage.m_status = ResponseStatus::UPDATE;

            rapidjson::Value valueWhite(rapidjson::kObjectType);
            valueWhite.AddMember("color", 'W', allocator);
            updateMessage.m_jsonData = valueToString(valueWhite);

            updateMessage.toJSON(json);
            m_session->write(json);

            rapidjson::Value valueBlack(rapidjson::kObjectType);
            valueBlack.AddMember("color", 'B', allocator);
            updateMessage.m_jsonData = valueToString(valueBlack);

            updateMessage.toJSON(json);
            auto sessions = m_session->getRoom().getSessions();
            if (sessions[0]->getId() != m_session->getId()) {
                sessions[0]->write(json);
            } else {
                sessions[1]->write(json);
            }
        }

        Response updateMessage;
        updateMessage.m_type = RequestType::NEW_READY;
        updateMessage.m_status = ResponseStatus::UPDATE;

        rapidjson::Value value(rapidjson::kObjectType);
        value.AddMember("user", rapidjson::Value(rapidjson::kObjectType), allocator);
        value["user"].AddMember("id", m_session->getUser().getId(), allocator);

        updateMessage.m_jsonData = valueToString(value);

        std::string json;
        updateMessage.toJSON(json);
        m_session->broadcast(json);
    }

    bool MoveFigure::isValid() {
        m_response.m_type = RequestType::MOVE_FIGURE;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (!m_session->userInMainRoom() && m_session->getGameRoom().gameStarted()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        if (doc.Parse(m_request->m_jsonData.data()).HasParseError() ||
            !doc.HasMember("id") || !doc["id"].IsUint64() ||
            !doc.HasMember("pos-to") || !doc["pos-to"].IsArray() ||
            doc["pos-to"].Size() != 2) {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        for (auto& value: doc["pos-to"].GetArray()) {
            if (!value.IsUint64()) {
                m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
            }
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void MoveFigure::execute() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        doc.Parse(m_request->m_jsonData.data());

        const auto figureId = doc["id"].GetUint64();
        const auto x = doc["pos-to"][0].GetUint64();
        const auto y = doc["pos-to"][1].GetUint64();

        std::uint64_t time = m_session->makeMove(figureId, x, y);
        if (time != -1) {
            {
                rapidjson::Value value(rapidjson::kObjectType);
                value.AddMember("time", time, allocator);

                m_response.m_jsonData = valueToString(value);
            }

            Response updateMessage;
            updateMessage.m_type = RequestType::LISTEN_MOVE;
            updateMessage.m_status = ResponseStatus::UPDATE;

            rapidjson::Value value(rapidjson::kObjectType);
            value.AddMember("id", m_session->getUser().getId(), allocator);

            rapidjson::Value arrayValue(rapidjson::kArrayType);
            arrayValue.PushBack(x, allocator);
            arrayValue.PushBack(y, allocator);
            value.AddMember("pos", arrayValue, allocator);

            value.AddMember("time", time, allocator);

            updateMessage.m_jsonData = valueToString(value);

            std::string json;
            updateMessage.toJSON(json);
            m_session->broadcast(json);
        } else {
            m_response.m_status = ResponseStatus::INTERNAL_SERVER_ERROR;
        }
    }

}  // namespace Handlers
