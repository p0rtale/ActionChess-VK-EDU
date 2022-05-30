#include "Figure.hpp"

Figure::Figure(Tile position_,collider collide_,std::string img_,unsigned int ID_,TypeFigure type_,char color_,bool player_) : Sprite(position_,collide_,img_,ID_,type_,color_){
    player = player_;
    fps = 24;
}

void Figure::update(sf::Event event,sf::RenderWindow* window,std::shared_ptr<BoardTable> board){
    Tile pos = {0,0};
    if (!isInFlight && player == true){
       pos = wait_pressing(event,window);
    } else if (player == true){
        pos = board->touch_board(event, window);
    }
    if (true){ // старт полута 
        isInFlight = false;
    }
    if (isInFlight){
        move();
    }
}
// "rook","knight","bishop","queen","king","pawn"
void Figure::move(){

    switch (type)
    {
    case TypeFigure::ROOK:
        if (heading == HeadingMove::RIGHT){
            collide.x += speed;
        } else if (heading == HeadingMove::LEFT){
            collide.x -= speed;
        } else if (heading == HeadingMove::UP){
            collide.y += speed;
        } else if (heading == HeadingMove::DOWN){
            collide.y -= speed;
        }
        if (collide.x == collide_to.x && collide.y == collide_to.y){
            // конец двидения
            isInFlight = false;
        }
        break;
    case TypeFigure::KNIGHT:
        if (turn == false){
            collide.y += speed;
            if (collide.x == collide_to.x && collide.y == collide_to.y){
                turn = true;
                if (heading == HeadingMove::RIGHT){
                    collide_to.x +=  + collide.width;
                }
                if (heading == HeadingMove::LEFT){
                    collide_to.x -= collide.width;
                }
            }
        } else {
            if (heading == HeadingMove::RIGHT){
                collide.x += speed;
            } else if (heading == HeadingMove::LEFT){
                collide.x -= speed;
            }
            if (collide.x == collide_to.x && collide.y == collide_to.y)
            {
                // конец двидения
                isInFlight = false;
            }
        }
        break;
    case TypeFigure::BISHOP:

        if (heading == HeadingMove::RIGHT_UP){
            collide.x += speed;
            collide.y += speed;
        } 
        else if (heading == HeadingMove::RIGHT_DOWN){
            collide.x += speed;
            collide.y -= speed;
        } 
        else if (heading == HeadingMove::LEFT_UP){
            collide.x -= speed;
            collide.y += speed;
        }
        else if (heading == HeadingMove::LEFT_DOWN){
            collide.x -= speed;
            collide.y -= speed;
        }
        if (collide.x == collide_to.x && collide.y == collide_to.y)
            {
                // конец двидения
                isInFlight = false;
            }
        break;
    case TypeFigure::QUEEN:

        if (heading == HeadingMove::RIGHT){
            collide.x += speed;
        }
        else if (heading == HeadingMove::LEFT){
            collide.x -= speed;
        }
        else if (heading == HeadingMove::UP){
            collide.y += speed;
        }
        else if (heading == HeadingMove::DOWN){
            collide.y -= speed;
        }
        else if (heading == HeadingMove::RIGHT_UP){
            collide.x += speed;
            collide.y += speed;
        }
        else if (heading == HeadingMove::RIGHT_DOWN){
            collide.x += speed;
            collide.y -= speed;
        }
        else if (heading == HeadingMove::LEFT_UP){
            collide.x -= speed;
            collide.y += speed;
        }
        else if (heading == HeadingMove::LEFT_DOWN){
            collide.x -= speed;
            collide.y -= speed;
        }
        if (collide.x == collide_to.x && collide.y == collide_to.y)
        {
            // конец двидения
            isInFlight = false;
        }
        break;
    case TypeFigure::KING:

        if (heading == HeadingMove::RIGHT){

            collide.x += speed;
        }
        else if (heading == HeadingMove::LEFT){

            collide.x -= speed;
        }
        else if (heading == HeadingMove::UP){

            collide.y += speed;
        }
        else if (heading == HeadingMove::DOWN){

            collide.y -= speed;
        }
        else if (heading == HeadingMove::RIGHT_UP){

            collide.x += speed;
            collide.y += speed;
        }
        else if (heading == HeadingMove::RIGHT_DOWN){

            collide.x += speed;
            collide.y -= speed;
        }
        else if (heading == HeadingMove::LEFT_UP){

            collide.x -= speed;
            collide.y += speed;
        }
        else if (heading == HeadingMove::LEFT_DOWN){

            collide.x -= speed;
            collide.y -= speed;
        }
        if (collide.x == collide_to.x && collide.y == collide_to.y)
        {
            // конец двидения
            isInFlight = false;
        }
        break;
    case TypeFigure::PAWN:

        if (heading == HeadingMove::RIGHT){

            collide.x += speed;
        }
        else if (heading == HeadingMove::RIGHT_UP){

            collide.x += speed;
            collide.y += speed;
        }
        else if (heading == HeadingMove::LEFT_UP){

            collide.x -= speed;
            collide.y += speed;
        }
        if (collide.x == collide_to.x && collide.y == collide_to.y)
        {
            // конец двидения
            isInFlight = false;
        }
        break;
    default:
        break;
    }
}

void Figure::start_move(){
    // получим
    int time = 0;
    switch (type)
    {
    case TypeFigure::ROOK:
        if (pos_to.column == position.column && pos_to.row > position.row){

            heading = HeadingMove::UP;
            distance = (pos_to.row - position.row) * collide.height;
            collide_to.y = collide.y + distance;
            collide_to.x = collide.x;
        }
        else if (pos_to.column == position.column && pos_to.row < position.row)
        {
            heading = HeadingMove::DOWN;
            distance = (position.row - pos_to.row) * collide.height;
            collide_to.y = collide.y - distance;
            collide_to.x = collide.x;
        }
        else if (pos_to.column > position.column && pos_to.row == position.row)
        {
            heading = HeadingMove::RIGHT;
            distance = (pos_to.column - position.column) * collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y;
        }
        else if (pos_to.column < position.column && pos_to.row == position.row)
        {
            heading = HeadingMove::LEFT;
            distance = (position.column - pos_to.column) * collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y;
        }
        position = pos_to;
        speed = static_cast<int>(distance / fps);
        break;
    case TypeFigure::KNIGHT:

        if (pos_to.column > position.column){

            heading = HeadingMove::RIGHT;
            distance = collide.width * 3;
            collide_to.x = collide.x;
            collide_to.y = collide.y + 2 * collide.height;
        } 
        else if (pos_to.column < position.column) {
            heading = HeadingMove::LEFT;
            distance = collide.width * 3;
            collide_to.x = collide.x;
            collide_to.y = collide.y + 2 * collide.height;
        }
        position = pos_to;
        speed = static_cast<int>(distance / fps);
        break;
    case TypeFigure::BISHOP:

        if (pos_to.column > position.column && pos_to.row > position.row){

            heading = HeadingMove::RIGHT_UP;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column < position.column && pos_to.row > position.row){
            
            heading = HeadingMove::LEFT_UP;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column > position.column && pos_to.row < position.row){
           
            heading = HeadingMove::RIGHT_DOWN;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y - distance;
        } 
        else if (pos_to.column < position.column && pos_to.row < position.row){
            
            heading = HeadingMove::LEFT_DOWN;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y - distance;
        }
        speed = static_cast<int>(distance / fps);
        position = pos_to;
        break;
    case TypeFigure::QUEEN:
        if (pos_to.column == position.column && pos_to.row > position.row){
            
            heading = HeadingMove::UP;
            distance = (pos_to.row - position.row)*collide.height;
            collide_to.x = collide.x;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column == position.column && pos_to.row < position.row){
            
            heading = HeadingMove::DOWN;
            distance = (position.row - pos_to.row)*collide.height;
            position = pos_to;
            collide_to.x = collide.x;
            collide_to.y = collide.y - distance;
        }
        else if (pos_to.column > position.column && pos_to.row == position.row){
            
            heading = HeadingMove::RIGHT;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y;
        }
        else if (pos_to.column < position.column && pos_to.row == position.row){
            
            heading = HeadingMove::LEFT;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y;
        }
        else if (pos_to.column > position.column && pos_to.row > position.row){
            
            heading = HeadingMove::RIGHT_UP;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column < position.column && pos_to.row > position.row){
            
            heading = HeadingMove::LEFT_UP;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column > position.column && pos_to.row < position.row){
            
            heading = HeadingMove::RIGHT_DOWN;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y - distance;
        } 
        else if (pos_to.column < position.column && pos_to.row < position.row){
            
            heading = HeadingMove::LEFT_DOWN;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y - distance;
        }
        position = pos_to;
        speed = static_cast<int>(distance / fps);
        break;
    case TypeFigure::KING:

        if (pos_to.column == position.column && pos_to.row > position.row){
            
            heading = HeadingMove::UP;
            distance = (pos_to.row - position.row)*collide.height;
            collide_to.x = collide.x;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column == position.column && pos_to.row < position.row){
           
            heading = HeadingMove::DOWN;
            distance = (position.row - pos_to.row)*collide.height;
            collide_to.x = collide.x;
            collide_to.y = collide.y - distance;
        } 
        else if (pos_to.column > position.column && pos_to.row == position.row){
            heading = HeadingMove::RIGHT;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y;
        } 
        else if (pos_to.column < position.column && pos_to.row == position.row){
            
            heading = HeadingMove::LEFT;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y;
        } 
        else if (pos_to.column > position.column && pos_to.row > position.row){
            heading = HeadingMove::RIGHT_UP;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column < position.column && pos_to.row > position.row){
            
            heading = HeadingMove::LEFT_UP;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column > position.column && pos_to.row < position.row){
            
            heading = HeadingMove::RIGHT_DOWN;;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y - distance;
        } else if (pos_to.column < position.column && pos_to.row < position.row){
            heading = HeadingMove::LEFT_DOWN;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y - distance;
        }
        position = pos_to;
        speed = static_cast<int>(distance / fps);
        break;
    case TypeFigure::PAWN:

        if (pos_to.column == position.column && pos_to.row > position.row){
            
            heading = HeadingMove::UP;
            distance = (pos_to.row - position.row)*collide.height;
            collide_to.x = collide.x;
            collide_to.y = collide.y + distance;
        }
        else if (pos_to.column > position.column && pos_to.row > position.row){
            
            heading = HeadingMove::RIGHT_UP;
            distance = (pos_to.column - position.column)*collide.width;
            collide_to.x = collide.x + distance;
            collide_to.y = collide.y + distance;
        } 
        else if (pos_to.column < position.column && pos_to.row > position.row){
            
            heading = HeadingMove::LEFT_UP;
            distance = (position.column - pos_to.column)*collide.width;
            collide_to.x = collide.x - distance;
            collide_to.y = collide.y + distance;
        }
        position = pos_to;
        speed = static_cast<int>(distance / fps);
        break;
    default:
        break;
    }
}




