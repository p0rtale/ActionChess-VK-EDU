#pragma once


#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "Variables.hpp"
#include "Assets.hpp"
#include <functional>

class Button: public BasicWidget{
// Класс заполняемых тектовых полей
public:
    Button(sf::Texture inp_back_im, sf::Texture inp_edge_im,sf::Color inp_edge_color, sf::Color inp_inactive_color,sf::Color inp_fill_color_default, sf::Color inp_fill_when_mouse_over, sf::Vector2f inp_scale_when_pressed, sf::Vector2f inp_scale, sf::Vector2f inp_pos, sf::Text inp_caption, \
     std::function<void()> inp_handler):background_image(inp_back_im),edge_image(inp_edge_im),scale_factor(inp_scale), pos(inp_pos),\
     caption(inp_caption), handler(inp_handler), edge_color(inp_edge_color),fill_color_default(inp_fill_color_default),fill_when_mouse_over(inp_fill_when_mouse_over) ,scale_when_pressed(inp_scale_when_pressed),inactive_color(inp_inactive_color){
                background.setOrigin(sf::Vector2f(background.getLocalBounds().width/2,background.getLocalBounds().height/2));
                edge.setOrigin(sf::Vector2f(edge.getLocalBounds().width/2,edge.getLocalBounds().height/2));
                caption.setOrigin(sf::Vector2f(caption.getLocalBounds().width/2,caption.getLocalBounds().height/2));

                background.setTexture(background_image);
                background.setPosition(pos.x*scale_factor.x,pos.y*scale_factor.y);  
                background.setScale(scale_factor);
                background.setColor(fill_color_default);
                edge.setTexture(edge_image);
                edge.setPosition(pos.x*scale_factor.x,pos.y*scale_factor.y);  
                edge.setScale(scale_factor);
                edge.setColor(edge_color);

                background.setOrigin(sf::Vector2f(background.getLocalBounds().width/2,background.getLocalBounds().height/2));
                edge.setOrigin(sf::Vector2f(edge.getLocalBounds().width/2,edge.getLocalBounds().height/2));
                caption.setOrigin(sf::Vector2f(caption.getLocalBounds().width/2,caption.getLocalBounds().height/2));
                sf::Rect<float> textbox = caption.getGlobalBounds();
                sf::Rect<float> button_box = background.getGlobalBounds();
                if ((textbox.width  + MENU_BUTTON_SIZE_OFFSET > button_box.width) || (textbox.height  + MENU_BUTTON_SIZE_OFFSET > button_box.height)){
                    scale_factor = sf::Vector2f(scale_factor.x*((textbox.width  + MENU_BUTTON_SIZE_OFFSET )/button_box.width),scale_factor.y*((textbox.height  + MENU_BUTTON_SIZE_OFFSET )/button_box.height));
                    background.setScale(scale_factor);
                    edge.setScale(scale_factor);
                }
                button_box = edge.getGlobalBounds();

                caption.setPosition(sf::Vector2f(button_box.left + button_box.width/2 - textbox.width/2,button_box.top + button_box.height/2 - textbox.height));
            };
    
    Button() {};
    ~Button() {};

    void on_click_release(sf::RenderWindow* window)override;
    void on_click_press(sf::RenderWindow* window) override;
    void on_mouse_over(sf::RenderWindow* window)override;
    void on_type(sf::RenderWindow* window, sf::Event event)override;
    void draw(sf::RenderWindow* window) override;



protected:
    void animate_click();
    std::function<void()> handler;
    mouseState clicked = FAR;
    bool visible = true; 
    bool active = true;
    sf::Text caption;
    sf::Texture background_image;
    sf::Texture edge_image;
    sf::Sprite background;
    sf::Sprite edge;
    sf::Vector2f pos;
    sf::Vector2f scale_factor;
    sf::Texture inp_edge_im;
    sf::Color edge_color;
    sf::Color fill_color_default;
    sf::Color fill_when_mouse_over; 
    sf::Vector2f scale_when_pressed;
    sf::Color inactive_color;
};  