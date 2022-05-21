#pragma once
#include "BasicView.hpp"
#include "BasicModel.hpp"

class BasicController{
//Абстрактный класс для controller
public:
    virtual void init();    
    virtual void run();

    BasicController(BasicController const& other) = delete;
    BasicController &operator=(BasicController const& other) = delete;
    BasicController(BasicController&& that) = delete;
    BasicController &operator=(BasicController&& that) = delete;
    friend void swap(BasicController& lhs, BasicController& rhs) = delete;
    BasicController();
    BasicController(BasicView*& view, BasicModel*& model): view(view),model(model){};
    virtual ~BasicController() = default;
protected:
    BasicView* view;
    BasicModel* model;
};