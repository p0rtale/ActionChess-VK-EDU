#pragma once

#include "Handler.hpp"

class StartGame: public Handler {
private:
    bool isValid() override;

    void execute() override;
};

class MakeMove: public Handler {
private:
    bool isValid() override;

    void execute() override;
};
