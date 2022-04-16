#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.h"


class Figure : public Sprite{
private:
    int id;
    char color;
    bool Alive;
    bool isInFlight;
public:
    Figure();
    void update() override;
    bool del();
    bool isInFlight();
    int getID();
    void move();
};