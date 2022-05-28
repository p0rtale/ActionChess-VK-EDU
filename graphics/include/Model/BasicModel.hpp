#pragma once


#include "Client.hpp"
class BasicModel{
//Абстрактный класс для model
public:
    virtual void init() = 0;    
    virtual void tick() = 0;

    BasicModel(BasicModel const& other) = delete;
    BasicModel &operator=(BasicModel const& other) = delete;
    BasicModel(BasicModel&& that) = delete;
    BasicModel &operator=(BasicModel&& that) = delete;
    friend void swap(BasicModel& lhs, BasicModel& rhs) = delete;
    BasicModel() = default;
    virtual ~BasicModel() = default;
protected:
    Client* c;// TODO: расскоментировать после реализации сетевой части
};