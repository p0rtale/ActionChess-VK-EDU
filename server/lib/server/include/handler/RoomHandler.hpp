#pragma once

#include "Handler.hpp"

class CreateRoom: public Handler {
private:
    bool isValid() override;

    void execute() override;
};

class JoinRoom: public Handler {
private:
    bool isValid() override;

    void execute() override;
};

class LeaveRoom: public Handler {
private:
    bool isValid() override;

    void execute() override;
};

class GetAllRooms: public Handler {
private:
    bool isValid() override;

    void execute() override;
};

class WriteMessage: public Handler {
private:
    bool isValid() override;

    void execute() override;
};
