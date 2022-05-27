#include "Handler.hpp"

#include "Session.hpp"

namespace Handlers {

    Handler::Handler(const Request* request, Session* session)
        : m_request(request), m_session(session) {}

    void Handler::run() {
        if (isValid()) {
            execute();
        }
        sendResponse();
    }

    void Handler::sendResponse() {
        std::string responseStr;
        m_response.toJSON(responseStr);
        m_session->write(responseStr);
    }

    bool Undefined::isValid() {
        m_response.m_type = RequestType::UNDEFINED;
        m_response.m_status = ResponseStatus::METHOD_NOT_ALLOWED;

        return false;
    }

    void Undefined::execute() {}

}  // namespace Handlers
