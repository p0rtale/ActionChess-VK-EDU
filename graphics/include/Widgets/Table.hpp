#pragma once


#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "Variables.hpp"
#include "Assets.hpp"
#include <functional>
#include "Slidebar.hpp"
#include "MenuModel.hpp"

class Table: public BasicWidget{
// Класс отображаемых таблиц данных
public:
    Table(sf::Texture inp_back_im, sf::Texture inp_slide_stick_im, sf::Texture inp_slider_im, sf::Vector2f inp_slider_offset, sf::Rect<float> inp_text_zone, sf::Color inp_selected_color,\
    sf::Color inp_fill_color_default,sf::Vector2f inp_scale, sf::Vector2f inp_pos,  sf::Text inp_caption, \
     std::function<void()> inp_handler):background_image(inp_back_im),scale_factor(inp_scale), pos(inp_pos),\
     caption(inp_caption), handler(inp_handler), fill_color_default(inp_fill_color_default),selected_color(inp_selected_color), text_zone(inp_text_zone){

                background.setTexture(background_image);
                background.setPosition(pos.x*scale_factor.x,pos.y*scale_factor.y);  
                background.setScale(scale_factor);
                
                slider.set_scale_factor(scale_factor);
                slider.set_slide_stick_texture(inp_slide_stick_im);
                slider.set_slider_texture(inp_slider_im);
                slider.set_slide_stick_pos(sf::Vector2f((pos.x+inp_slider_offset.x),(pos.y+inp_slider_offset.y)));
                table_texture.create(1000,1000);
                text_table.setTexture(table_texture.getTexture());
               text_table.setPosition((pos.x+text_zone.left)*scale_factor.x,(pos.y+text_zone.top)*scale_factor.y);
               //text_table.setScale(scale_factor);
                text_table.setTextureRect(sf::IntRect(0,0,text_zone.width*scale_factor.x,text_zone.height*scale_factor.y));

                caption.setPosition(0,0);

            };
    
    Table() {};
    ~Table() {};

    void on_click_release(sf::RenderWindow* window)override;
    void on_click_press(sf::RenderWindow* window) override;
    void on_mouse_over(sf::RenderWindow* window)override;
    void on_type(sf::RenderWindow* window, sf::Event event)override;
    void draw(sf::RenderWindow* window) override;

    void set_rooms(std::vector<Rooms> inp_rooms);
protected:
    void animate_click();
    std::function<void()> handler;
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
    sf::Color selected_color;
    std::vector<Rooms> rooms;
    std::vector<sf::String> rooms_str;
    std::vector<sf::Text> rooms_caption;
    Slidebar slider;
    float slider_offset =0;
    int selected = 0;
    float selected_offset = 0;
    sf::Rect<float> text_zone;
    sf::RenderTexture table_texture;
    sf::Sprite text_table;
    void render_texture();
    void parse_rooms();
    sf::Clock move_timer;
};  