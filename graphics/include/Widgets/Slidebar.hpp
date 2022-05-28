#pragma once 

#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "Variables.hpp"
#include "Assets.hpp"
class Slidebar: public BasicWidget{
// Класс ползунка бокового
public:
    Slidebar(sf::Texture inp_slide_stick_im,sf::Texture inp_slider_im, sf::Vector2f inp_scale , sf::Vector2f inp_pos){ //пример как надо будет переписать конструкторы
                set_slide_stick_texture(inp_slide_stick_im);
                set_slider_texture(inp_slider_im);
                set_scale_factor(scale_factor);
                set_slide_stick_pos(inp_pos);
            };
    
    Slidebar() {};
    ~Slidebar() {};

    void set_slide_stick_texture(sf::Texture inp_slide_stick_im){
        slide_stick_image = inp_slide_stick_im;
        slide_stick.setTexture(slide_stick_image);
    }
    void set_slider_texture(sf::Texture inp_slider_im){
        slider_image =  inp_slider_im;
        slider.setTexture(slider_image);
    }
    void set_slide_stick_pos(sf::Vector2f pos){
        slide_stick.setPosition(pos.x*scale_factor.x,pos.y*scale_factor.y);  
        sf::Rect<float> box = slide_stick.getGlobalBounds();

        slider.setPosition(box.left+box.width/2-slider.getGlobalBounds().width/2,box.top);  

    }

    void set_scale_factor(sf::Vector2f inp_scale_factor){
        scale_factor = inp_scale_factor;
        slide_stick.setScale(scale_factor);

        slider.setScale(scale_factor);
    }
    void on_click_release(sf::RenderWindow* window)override;
    void on_click_press(sf::RenderWindow* window) override;
    void on_mouse_over(sf::RenderWindow* window)override;
    void on_type(sf::RenderWindow* window, sf::Event event)override;
    void draw(sf::RenderWindow* window) override;


protected:
    sf::Texture slider_image;
    sf::Texture slide_stick_image;
    sf::Sprite slider;
    sf::Sprite slide_stick;
    sf::Vector2f pos;
    sf::Rect<float> active_zone;
    sf::Vector2f scale_factor;
    float mouse_delta=0.f;
    float mouse_prev_pos = 0.f;

};