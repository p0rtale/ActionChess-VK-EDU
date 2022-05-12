#include "Handler.hpp"

#include "Session.hpp"

namespace Handlers {

    bool StartGame::isValid() {
        m_response.m_type = RequestType::START_GAME;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (m_session->userInMainRoom()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void StartGame::execute() {
        
    }

    bool MakeMove::isValid() {
        m_response.m_type = RequestType::MAKE_MOVE;

        if (!m_session->isAcknowleged()) {
            m_response.m_status = ResponseStatus::FAILED_DEPENDENCY;
        } else if (m_session->userInMainRoom()) {
            m_response.m_status = ResponseStatus::OK;
        } else {
            m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;
        }

        return m_response.m_status == ResponseStatus::OK;
    }

    void MakeMove::execute() {

    }

}  // namespace Handlers
