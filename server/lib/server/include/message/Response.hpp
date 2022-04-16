#pragma once

#include "Message.hpp"

struct Response: public Message {
    RequestType m_type { RequestType::ERROR };

    int m_status { 0 };

    std::string m_data {};

    void parseJSON(const std::string& json) override;

    void toJSON(std::string& json) const override;
};
