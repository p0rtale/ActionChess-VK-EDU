#pragma once 

#include <SFML/Graphics.hpp>
#include "BasicStage.hpp"


class MenuStage: public BasicStage{

public:
    void init() override;
    BasicStage* run() override;
    ~MenuStage() override;
    MenuStage(sf::RenderWindow* inp_window);

private:
    
};





