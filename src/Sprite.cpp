#include "Sprite.hpp"

Sprite::Sprite(const Sprite& r){
    position = r.position;

    collide = r.collide;

    sprite = r.sprite;

    texture = r.texture;

    ID = r.ID;

    type = r.type;

    color = r.color;
}

Sprite::Sprite(){}

Sprite::Sprite(Tile position_,collider collide_,std::string img_,unsigned int ID_,TypeFigure type_,char color_){
    // присваиваем праметры соответствующим полям
    position = position_;
    collide = collide_;
    ID = ID_;
    type = type_;
    color = color_;
    img = img_;
}

sf::Sprite& Sprite::getSprite(){
    return sprite;
}

int Sprite::getID(){
    return ID;
}

void Sprite::draw(sf::RenderWindow* window){
    texture.loadFromFile(img);
    // Связываем спрайт и текстуру
    sprite.setTexture(texture);
    // Масштабирование спрайта
    float WidgetWidth = (float) collide.width / (float) texture.getSize().x;
    float WidgetHeight = (float) collide.height / (float) texture.getSize().y;
    sprite.setScale(WidgetWidth, WidgetHeight);
    // выстовка по координатам спрайта
    sprite.setPosition(collide.x,collide.y);
    window->draw(sprite);
}

Tile Sprite::wait_pressing(sf::Event event,sf::RenderWindow* window){
    sf::Vector2i pos= sf::Mouse::getPosition(*window);//забираем коорд курсора
    if (event.type == sf::Event::MouseButtonPressed){//если нажата клавиша мыши
		if (event.key.code == sf::Mouse::Left){//а именно левая
	        if (sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
            {
                return position;
            }
        }
        return {0,0};
    }
    return {0,0};
}
