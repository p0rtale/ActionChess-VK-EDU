#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

enum class TypeFigure {
   ROOK,
   KNIGHT,
   BISHOP,
   QUEEN,
   KING ,
   PAWN,
   CAGE
};

struct collider
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    collider (const collider& other)
    {
        this->x = other.x;
        this->y = other.y;
        this->width = other.width;
        this->height = other.height;
    }
    collider(){
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }
    collider(int x_,int y_, int width_, int height_) {
        x = x_;
        y = y_;
        width = width_;
        height = height_;
    }
};

struct Tile 
{
    unsigned int row = 0;
    unsigned int column = 0;

    Tile(){
        row = 0;
        column = 0;
    }

    Tile (const Tile& other)
    {
        this->row = other.row;
        this->column = other.column;
    }
    Tile(unsigned int row_, unsigned int column_){
        row = row_;
        column = column_;
    }
};

class Sprite
{
protected:

    Tile position;

    collider collide;

    sf::Sprite sprite;

    sf::Texture texture;

    unsigned int ID;

    TypeFigure type;

    char color;

    std::string img;

public:
    Sprite();

    Sprite(const Sprite& r);

    Sprite(Tile position_,collider collide_,std::string img_,unsigned int ID_,TypeFigure type_,char color_);
    
    sf::Sprite& getSprite();
    
    Tile wait_pressing(sf::Event event,sf::RenderWindow* window);
    
    int getID();

    void draw(sf::RenderWindow* window);
};