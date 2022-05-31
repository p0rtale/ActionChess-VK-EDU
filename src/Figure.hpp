#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "Sprite.hpp"
#include "BoardTable.hpp"

enum class HeadingMove {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    RIGHT_UP,
    LEFT_UP,
    RIGHT_DOWN,
    LEFT_DOWN
};

class Figure : public Sprite
{
private:

    bool Alive = true;

    bool isInFlight = false;

    bool player;

    bool turn = false;

    HeadingMove heading;

    Tile pos_to;

    collider collide_to;

    int distance;

    int speed;

    int fps;

    std::vector<collider> vec_collide(sf::Vector2i resolution);

public:

    Figure(Tile position_,collider collide_,std::string img_,unsigned int ID_,TypeFigure type_,char color_,bool player_);
    
    void update(sf::Event event,sf::RenderWindow* window,std::shared_ptr<BoardTable> board);
    
    bool get_isInFlight();

    void move();

    void start_move();
};