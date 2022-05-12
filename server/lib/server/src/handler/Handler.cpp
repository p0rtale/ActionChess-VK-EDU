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

}  // namespace Handlers
