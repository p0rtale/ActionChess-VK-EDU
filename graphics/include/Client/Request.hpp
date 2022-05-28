#pragma once

#include "Message.hpp"

class Request: public Message {
public:
    RequestType m_type = RequestType::DEFAULT;

    std::string m_data;

    void parseJSON(const std::string& json) override;

    void toJSON(std::string& json) const override;
    ~Request() = default;
};