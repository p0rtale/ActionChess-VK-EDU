#pragma once

#include "Message.hpp"

class Request: public Message {
public:
    RequestType m_type = RequestType::DEFAULT;

    std::string m_jsonData;

    void parseJSON(const std::string& json) override;

    void toJSON(std::string& json) const override;
};
