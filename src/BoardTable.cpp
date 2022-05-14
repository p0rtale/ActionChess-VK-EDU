#include "BoardTable.hpp"

BoardTable::BoardTable(sf::Vector2i resolution){

    std::vector<collider> collide_ = vec_collide(resolution);
    Tile position_ = {1,1};
    std::vector<std::string> img = {"images/black_cage.png","images/white_cage.png"}; 
    int ID = 33, ID_;
    std::string type_ = "cage";
    char color_[2] = {'b','w'};
    for (int i = 0; i < 64; ++i){
        ID_ = ID + i;
        Figures.push_back(Sprite(position_,collide_[i],img[i % 2],ID_,type_,color_[i % 2]))
    }
}

std::vector<collider> BoardTable::vec_collide(sf::Vector2i resolution)
{
    collider collide_ = {resolution.x / 16, resolution.x / 16, resolution.x / 2 - (resolution.x / 16) * 4,  resolution.y / 2 + (resolution.x / 16) * 4};
    std::vector<collider> vec;
    for (int i = 0; i < 8; ++i){
        collide_.y = collide_.y - i * (resolution.x / 16);
        for (int j = 0; j < 8; ++j){
            collide_.y = collide_.y + i * (resolution.x / 16);
            vec.push_back(collide_);
        }
    }
    return vec;
}

std::vector<sf::Sprite> BoardTable::getSprite(){
    return Figures;
}

Tile BoardTable::touch_board(sf::Event event,sf::RenderWindow& window){
    Tile pos = {0,0};
    for (int i = 0; i < Figures.size(); ++i){
        pos = Figures[i].wait_pressing(event,window);
    }
    return pos;
}




