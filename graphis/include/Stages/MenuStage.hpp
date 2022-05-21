#pragma once 

#include <SFML/Graphics.hpp>
#include "BasicStage.hpp"


class MenuStage: public BasicStage{

public:
    void init(sf::RenderWindow* inp_window) override;
    BasicStage* run() override;
    ~MenuStage() override;

private:
    
};





