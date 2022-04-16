#pragma once

#include "Message.hpp"

struct Request: public Message {
    RequestType m_type { RequestType::ERROR };

    std::string m_data {};

    void parseJSON(const std::string& json) override;

    void toJSON(std::string& json) const override;
};
