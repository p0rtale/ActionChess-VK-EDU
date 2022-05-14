#include "Figure.hpp"

Figure::Figure(Tile position_,collider collide_,std::string img_,unsigned int ID_,std::string type_,char color_,bool player_) : Sprite(position_,collide_,img_,ID_,type_,color_){
    player = player_;
}

void Figure::update(sf::Event event,sf::RenderWindow& window,BoardTable& board){
    Tile pos = {0,0};
    if (!isInFlight && player == true){
       pos = wait_pressing(event,window);
    } else if (player == true){
        pos = board.touch_board(event, window);
    }
    else {}
    }
}

