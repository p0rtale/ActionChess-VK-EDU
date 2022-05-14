#include "GroupFigure.hpp"

GroupFigure::GroupFigure(sf::Vector2i resolution,bool player_,char color_)
{
    player = player_;
    color = color_;
    std::vector<collider> collide_;
    std::vector<Tile> position_;
    std::vector<std::string> img;
    std::vector<int> ID_;
    std::vector<std::string> type_;
    if (player){
        collide_ = vec_collide(resolution,player);
        position_ = {{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{2,7},{2,8}};
        if (color == 'w'){
            img = {"images/w_rook.png","images/w_knight.png","images/w_bishop.png","images/w_queen.png","images/w_king.png","images/w_bishop.png","images/w_knight.png","images/w_rook.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png"};
            ID_ = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        }
        else {
            img = {"images/b_rook.png","images/b_knight.png","images/b_bishop.png","images/b_queen.png","images/b_king.png","images/b_bishop.png","images/b_knight.png","images/b_rook.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png"};
            ID_ = {17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
        }
        type_ = {"rook","knight","bishop","queen","king","bishop","knight","rook","pawn","pawn","pawn","pawn","pawn","pawn","pawn","pawn"};
    }
    else{
        collide_ = vec_collide(resolution,player);
        position_ = {{7,1},{7,2},{7,3},{7,4},{7,5},{7,6},{7,7},{7,8},{8,1},{8,2},{8,3},{8,4},{8,5},{8,6},{8,7},{8,8}};
        if (color == 'w'){
            img = {"images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_pawn.png","images/w_rook.png","images/w_knight.png","images/w_bishop.png","images/w_queen.png","images/w_king.png","images/w_bishop.png","images/w_knight.png","images/w_rook.png"};
            ID_ = {9,10,11,12,13,14,15,16,8,7,6,5,4,3,2,1};
        }
        else {
            img = {"images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_pawn.png","images/b_rook.png","images/b_knight.png","images/b_bishop.png","images/b_queen.png","images/b_king.png","images/b_bishop.png","images/b_knight.png","images/b_rook.png"};
            ID_ = {25,26,27,28,29,30,31,32,24,23,22,21,20,19,18,17};  
        }
        type_ = {"pawn","pawn","pawn","pawn","pawn","pawn","pawn","pawn","rook","knight","bishop","queen","king","bishop","knight","rook"};
    }
    for (int i = 0; i < 16; ++i){
        Figures.push_back(Figure(position_[i],collide_[i],img[i],ID_[i],type_[i],color_,player_));
    }
}

std::vector<collider> GroupFigure::vec_collide(sf::Vector2i resolution,bool player)
{

    std::vector<collider> vec;
    collider collide_;
    if (player){
        collide_ = {resolution.x / 16, resolution.x / 16, resolution.x / 2 - (resolution.x / 16) * 4,  (resolution.y / 2) + (resolution.x / 16) * 4};
    } else {
        collide_ = {resolution.x / 16, resolution.x / 16, resolution.x / 2 - (resolution.x / 16) * 4,  (resolution.y / 2) - (resolution.x / 16) * 2};
    }
    for (int i = 0; i < 2; ++i){
        collide_.y = collide_.y - i * collide_.height;
        for (int j = 0; j < 8; ++j){
            collide_.x = collide_.x + j * collide_.width;
            vec.push_back(collide_);
        }
    }
    return vec;
}

void GroupFigure::update(sf::Event event,sf::RenderWindow& window,BoardTable& board){
    for (int i = 0; i < Figures.size(); ++i){
        Figures[i].update(event,window,board);
    }
}