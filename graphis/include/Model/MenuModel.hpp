#pragma once
#include <SFML/Graphics.hpp>
#include "BasicModel.hpp"

class MenuModel: public BasicModel{
//Абстрактный класс для model
public:
    void init() override;    
    void tick() override;
    ~MenuModel() = default ;
};