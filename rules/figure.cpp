#include "tile.h"
#include "figure.h"

    Figure::Figure()
    {
        this->dead = false;
        this->inFlight = false;
        this->onCallDown = false;
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
