#include "BoardTable.hpp"

BoardTable::BoardTable(sf::Vector2i resolution){
    std::vector<collider> collide_ = vec_collide(resolution);
    std::vector<Tile> position_ = vec_Tile();
    std::array<std::string,16> img = {"images/black_cage.jpeg","images/white_cage.jpeg","images/black_cage.jpeg","images/white_cage.jpeg","images/black_cage.jpeg","images/white_cage.jpeg","images/black_cage.jpeg","images/white_cage.jpeg","images/white_cage.jpeg","images/black_cage.jpeg","images/white_cage.jpeg","images/black_cage.jpeg","images/white_cage.jpeg","images/black_cage.jpeg","images/white_cage.jpeg","images/black_cage.jpeg"}; 
    int ID = 0;
    TypeFigure type_ = TypeFigure::CAGE;
    std::array<char,16> color_ = {'b','w','b','w','b','w','b','w','w','b','w','b','w','b','w','b'};
    for (int i = 0; i < 64; ++i){
      Figures.emplace_back(new Sprite(position_[i],collide_[i],img[i % 16],ID,type_,color_[i % 16]));
    }
}

std::vector<Tile> BoardTable::vec_Tile(){
    std::vector<Tile> vec;
    Tile tile_ = {1,1};
    for (int i = 1; i <= 8; ++i){
        tile_.row = i;
        for (int j = 1; j <= 8; ++j){
            tile_.column = i;
            vec.push_back(tile_);
        }
    }
    return vec;
}

std::vector<collider> BoardTable::vec_collide(sf::Vector2i resolution)
{
    // TODO
    collider collide_ = { resolution.x / 2 - (resolution.x / 16) * 5,resolution.y / 2 + (resolution.x / 16) * 4,resolution.x / 16,resolution.x / 16};
    std::vector<collider> vec;
    for (int i = 0; i < 8; ++i){
        collide_.y = collide_.y - collide_.height;
        for (int j = 0; j < 8; ++j){
            collide_.x = collide_.x + collide_.width;
            vec.push_back(collide_);
        }
        collide_.x = resolution.x / 2 - (resolution.x / 16) * 5; // TODO
    }
    return vec;
}


Tile BoardTable::touch_board(sf::Event event,sf::RenderWindow* window){
    Tile pos = {0,0};
   // for (int i = 0; i < Figures.size(); ++i){
       for (int i = 0; i < 64; ++i){
        pos = Figures[i]->wait_pressing(event,window);
    }
    return pos;
}

void BoardTable::draw(sf::RenderWindow* window){
    for (int i = 0; i < 64; ++i){
        Figures[i]->draw(window);
    }
}




