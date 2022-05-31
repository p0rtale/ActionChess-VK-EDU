#include "GroupFigure.hpp"

void GroupFigure::draw(sf::RenderWindow* window){
    for (int i = 0; i < 16; ++i){
        Figures[i]->draw(window);
    }
}

GroupFigure::GroupFigure(sf::Vector2i resolution,bool player_,char color_)
{
    player = player_;
    color = color_;
    std::vector<collider> collide_;
    std::vector<Tile> position_;
    std::vector<std::string> img;
    std::vector<int> ID_;
    std::vector<TypeFigure> type_;
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
        type_ = {TypeFigure::ROOK,TypeFigure::KNIGHT,TypeFigure::BISHOP,TypeFigure::QUEEN,TypeFigure::KING,TypeFigure::BISHOP,TypeFigure::KNIGHT,TypeFigure::ROOK,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN};
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
        type_ = {TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::PAWN,TypeFigure::ROOK,TypeFigure::KNIGHT,TypeFigure::BISHOP,TypeFigure::QUEEN,TypeFigure::KING,TypeFigure::BISHOP,TypeFigure::KNIGHT,TypeFigure::ROOK};
    }

    for (int i = 0; i < 16; ++i){
       Figures.emplace_back(new Figure(position_[i],collide_[i],img[i],ID_[i],type_[i],color_,player_));
    }
}

std::vector<collider> GroupFigure::vec_collide(sf::Vector2i resolution,bool player)
{
    std::vector<collider> vec;
    collider collide_;
    collide_.height = resolution.x / 16;
    collide_.width = resolution.x / 16;
    if (player){ // TODO
        collide_ = {resolution.x / 2 - (resolution.x / 16) * 5,  (resolution.y / 2) + (resolution.x / 16) * 4, resolution.x / 16,  resolution.x / 16};
    } else {
        collide_ = {resolution.x / 2 - (resolution.x / 16) * 5,  (resolution.y / 2) - (resolution.x / 16) * 2, resolution.x / 16,  resolution.x / 16};
    }
    for (int i = 0; i < 2; ++i) {
        collide_.y = collide_.y -  collide_.height;
        for (int j = 0; j < 8; ++j){
            collide_.x = collide_.x + collide_.width;
            vec.push_back(collide_);
        }
        collide_.x = resolution.x / 2 - (resolution.x / 16) * 5; //TODO
    }
    return vec;
}

void GroupFigure::update(sf::Event event,sf::RenderWindow* window,std::shared_ptr<BoardTable> board){
    if (false){ // при условии соообщения удаления
        delFigure(1);
    }
    for (int i = 0; i < Figures.size(); ++i){
        Figures[i]->update(event,window,board);
    }
}
/*
void  GroupFigure::delFigure(int id){
    try{
        for (auto it = Figures.begin(); it != Figures.end(); ++it)
        { 
            if (id == it->getID()){
                Figures.erase(it);
                CountAlive--;
            }
        }
    }
    catch (const std::exception& e){
        std::cerr << "ERROR:" << e.what() << "\n";
    }  
}
*/

