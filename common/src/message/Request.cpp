#include "Request.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

void Request::parseJSON(const std::string& json) {
    rapidjson::Document doc;
    if (doc.Parse(json.data()).HasParseError() ||
        !doc.HasMember("type") || !doc["type"].IsString()) {
        m_type = RequestType::UNDEFINED;
    } else {
        m_type = strToType(doc["type"].GetString());
    }

    if (doc.HasMember("data")) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc["data"].Accept(writer);
        m_jsonData = std::string(buffer.GetString(), buffer.GetSize());
    } 
}

void Request::toJSON(std::string& json) const {
    rapidjson::Document doc;
    auto& alloc = doc.GetAllocator();
    doc.SetObject();

    rapidjson::Value value;

    const auto type = typeToStr(m_type);
    value.SetString(type.data(), alloc);
    doc.AddMember("type", value, alloc);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    json = std::string(buffer.GetString(), buffer.GetSize());
    if (!m_jsonData.empty()) {
        json.pop_back();
        json += ",\"data\":";
        json += m_jsonData;
        json += "}";
    }
    json += kMessageSeparator;    
}
