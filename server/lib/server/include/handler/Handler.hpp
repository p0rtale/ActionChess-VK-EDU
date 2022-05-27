#pragma once

#include <memory>

#include "Message.hpp"
#include "Request.hpp"
#include "Response.hpp"

class Session;

namespace Handlers {

    class Handler {
    public:
        Handler(const Request* request, Session* session);

        virtual ~Handler() = default;

        void run();

    protected:
        void sendResponse();

        virtual bool isValid() = 0;

        virtual void execute() = 0;

        const Request* m_request = nullptr;
        Session* m_session = nullptr;
        Response m_response;
    };

    class CreateRoom: public Handler {
    public:
        using Handler::Handler;

    private:
        bool isValid() override;

        void execute() override;
    };

    class JoinRoom: public Handler {
    public:
        using Handler::Handler;

    private:
        bool isValid() override;

        void execute() override;
    };

    class LeaveRoom: public Handler {
    public:
        using Handler::Handler;

    private:
        bool isValid() override;

        void execute() override;
    };

    class GetAllRooms: public Handler {
    public:
        using Handler::Handler;

    private:
        bool isValid() override;

        void execute() override;
    };

    class WriteMessage: public Handler {
    public:
        using Handler::Handler;

    private:
        bool isValid() override;

        void execute() override;
    };

    class StartGame: public Handler {
    public:
        using Handler::Handler;

    private:
        bool isValid() override;

        void execute() override;
    };

    class MakeMove: public Handler {
    public:
        using Handler::Handler;

    private:
        bool isValid() override;

        void execute() override;
    };

    class Undefined: public Handler {
    public:
        using Handler::Handler;

    private:
        bool isValid() override;

        void execute() override;
    };

    template<RequestType requestType>
    struct HandlerTrait {
        using type = void; 
    };

    template<>
    struct HandlerTrait<RequestType::CREATE_ROOM> {
        using type = CreateRoom;
    };

    template<>
    struct HandlerTrait<RequestType::JOIN_ROOM> {
        using type = JoinRoom;
    };

    template<>
    struct HandlerTrait<RequestType::LEAVE_ROOM> {
        using type = LeaveRoom;
    };

    template<>
    struct HandlerTrait<RequestType::GET_ALL_ROOMS> {
        using type = GetAllRooms;
    };

    template<>
    struct HandlerTrait<RequestType::WRITE_MESSAGE> {
        using type = WriteMessage;
    };

    template<>
    struct HandlerTrait<RequestType::MAKE_MOVE> {
        using type = MakeMove;
    };

    template<>
    struct HandlerTrait<RequestType::START_GAME> {
        using type = StartGame;
    };

    template<>
    struct HandlerTrait<RequestType::UNDEFINED> {
        using type = Undefined;
    };

    template<RequestType requestType>
    using HandlerTrait_t = typename HandlerTrait<requestType>::type;

    template<RequestType requestType>
    std::unique_ptr<Handler> createHandler(const Request* request, Session* session) {
        return std::make_unique<HandlerTrait_t<requestType>>(request, session);
    }

}  // namespace Handlers
