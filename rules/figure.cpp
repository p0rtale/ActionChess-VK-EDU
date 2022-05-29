#include "tile.h"
#include "figure.h"
#include <iostream>

    Figure::Figure()
    {
        this->dead = false;
        this->inFlight = false;
        this->onCallDown = false;
        this->atack = false;
    }
    bool Figure::isDead()
    {
        return dead;
    }
    bool Figure::isOnCallDown()
    {
        return onCallDown;
    }
    bool Figure::isInFlight()
    {
        return inFlight;
    }
    int Figure::getId()
    {
        return id;
    }
    char Figure::getType()
    {
        return type;
    }
    void Figure::setPosition(Tile new_position)
    {
        this->location = new_position;
    }
    Tile Figure::getPosition()
    {
        return this->location;
    }
    void Figure::die()
    {
        this->dead = true;
        std:: cout << this->id<< ": I died :(\n";
        this->location = Tile(0,0); // go to the cemetry
    }
    void Figure::setOnCallDown()
    {
        this->onCallDown = true;
    }
    void Figure::endCallDown()
    {
        this->onCallDown = false;
    }
    void Figure::setInFlight()
    {
        this->inFlight = true;
    }
    void Figure::endFlight()
    {
        this->inFlight = false;
    }
    char Figure::getColor()
    {
        return this->color;
    }
    bool Figure::isAtack()
    {
        return atack;
    }
    void Figure::setAtack(bool b)
    {
        this->atack = b;
    }