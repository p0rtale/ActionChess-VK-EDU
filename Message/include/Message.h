#pragma once
#include <string>

class Messege
{
    virtual ~Message() = default;

    virtual void parseJSON(const std::string& json) = 0;

    virtual void toJSON(std::string& json) const = 0;
    
};
