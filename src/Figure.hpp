#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.hpp"
#include "BoardTable.hpp"

class Figure : public Sprite{
private:
    bool Alive = true;
    bool isInFlight = false;
    bool player;
    std::vector<collider> vec_collide(sf::Vector2i resolution);
public:
    Figure(Tile position_,collider collide_,std::string img,unsigned int ID_,std::string type_,char color_,bool player_);
    void update(sf::Event event,sf::RenderWindow& window,BoardTable& board);
    bool del();
    bool isInFlight();
    int getID();
    void move();
};