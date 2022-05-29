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
        if (m_session->setReadyToPlay()) {
            rapidjson::Document doc;
            auto& allocator = doc.GetAllocator();

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
    }

    bool MakeMove::isValid() {
        m_response.m_type = RequestType::MAKE_MOVE;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (!m_session->userInMainRoom() && m_session->getGameRoom().gameStarted()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void MakeMove::execute() {

    }

}  // namespace Handlers
