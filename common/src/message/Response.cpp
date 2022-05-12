#include "Response.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

void Response::parseJSON(const std::string& json) {
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    m_type = strToType(doc["type"].GetString());
    m_status = static_cast<ResponseStatus>(doc["status"].GetInt());

    if (doc.HasMember("data")) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc["data"].Accept(writer);
        m_data = std::string(buffer.GetString(), buffer.GetSize());
    } 
}

void Response::toJSON(std::string& json) const {
    rapidjson::Document doc;
    auto& alloc = doc.GetAllocator();
    doc.SetObject();

    rapidjson::Value value;

    const auto type = typeToStr(m_type);
    value.SetString(type.c_str(), alloc);
    doc.AddMember("type", value, alloc);

    value.SetInt(static_cast<int>(m_status));
    doc.AddMember("status", value, alloc);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    json = std::string(buffer.GetString(), buffer.GetSize());
    if (!m_data.empty()) {
        json.pop_back();
        json += ",\"data\":";
        json += m_data;
        json += "}";
    }
    json += kMessageSeparator;
}
