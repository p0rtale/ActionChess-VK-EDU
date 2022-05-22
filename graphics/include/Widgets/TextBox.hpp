#pragma once

#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "Variables.hpp"

class TextBox: public BasicWidget{
// Класс заполняемых тектовых полей
public:
    TextBox(sf::Texture inp_back_im, sf::Vector2f inp_scale , sf::Vector2f inp_pos,sf::Rect<float> inp_active_zone, sf::Text inp_caption, sf::Text inp_hint,   sf::Text inp_databox):background_image(inp_back_im),scale_factor(inp_scale), pos(inp_pos), active_zone(inp_active_zone), caption(inp_caption), hint(inp_hint), databox(inp_databox){
                background.setTexture(background_image);
                background.setPosition(pos.x*scale_factor.x,pos.y*scale_factor.y);  
                background.setScale(scale_factor);
                      
            };
    TextBox() {};
    ~TextBox() {};

    void on_click_release(sf::RenderWindow* window, void* handler())override {};
    void on_click_press(sf::RenderWindow* window) override;
    void on_mouse_over(sf::RenderWindow* window)override;
    void on_type()override;
    void draw(sf::RenderWindow* window) const override;


protected:
    sf::Clock cursor_animation;
    bool show_cursor = false;
    bool focused;
    mouseState clicked = FAR;
    bool visible; 
    bool active;
    sf::Text caption;
    sf::Text hint;
    sf::Text databox;
    sf::String data;
    int data_height;
    int data_max_length;
    sf::Texture background_image;
    sf::Sprite background;
    sf::Vector2f pos;
    sf::Rect<float> active_zone;
    sf::Vector2f scale_factor;
};