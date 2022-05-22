#pragma once
#include <SFML/Graphics.hpp>
#include "BasicModel.hpp"

class MenuModel: public BasicModel{
//Абстрактный класс для model
public:
    void init() {};// TODO: override     
    void tick() {} ;// TODO: override 
    ~MenuModel() = default ;
};