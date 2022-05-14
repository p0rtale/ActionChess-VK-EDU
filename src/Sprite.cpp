#include "Sprite.hpp"

Sprite::Sprite(){}

Sprite::Sprite(Tile position_,collider collide_,std::string img_,unsigned int ID_,std::string type_,char color_){
    // присваиваем праметры соответствующим полям
    position = position_;
    collide = collide_;
    ID = ID_;
    type = type_;
    color = color_;
    // Загружаем фон в текстуру
    texture.loadFromFile(img_);
    // Связываем спрайт и текстуру
    sprite.setTexture(texture);
    // Масштабирование спрайта
    sprite.scale(collide.width,collide.height);
    // выстовка по координатам спрайта
    sprite.setPosition(collide.x,collide.y);
}

sf::Sprite Sprite::getSprite(){
    return sprite;
}
int Sprite::getID(){
    return ID;
}

Tile Sprite::wait_pressing(sf::Event event,sf::RenderWindow window){
    sf::Vector2i pos= sf::Mouse::getPosition(window);//забираем коорд курсора
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
