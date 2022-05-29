#pragma once

#include "Message.hpp"

class Response: public Message {
public:
    RequestType m_type = RequestType::DEFAULT;

    ResponseStatus m_status = ResponseStatus::OK;

    std::string m_data;

    void parseJSON(const std::string& json) override;

    void toJSON(std::string& json) const override;
    //~Response() = default;
};