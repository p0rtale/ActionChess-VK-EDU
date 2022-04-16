#pragma once

#include "Request.hpp"
#include "Response.hpp"

class Session;

class Handler {
public:
    Handler(const Request* request, Session* service);
 
    virtual ~Handler() = default;

    void run();

protected:

    void sendResponse();

    virtual bool isValid() = 0;

    virtual void execute() = 0;

    const Request* m_request { nullptr };
    Session* m_session { nullptr };
    Response m_response {};
};
