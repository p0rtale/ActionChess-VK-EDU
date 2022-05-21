#pragma once
#include "BasicController.hpp"

class MenuController: public BasicController{
public:
    void init() override;    
    void run() override;
    MenuController(BasicView* inp_view, BasicModel* inp_model){
        view = inp_view;
        model = inp_model;
    };

    ~MenuController() = default;
};