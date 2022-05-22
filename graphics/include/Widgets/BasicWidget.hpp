#pragma once

#include <SFML/Graphics.hpp>

enum mouseState  {
    FAR,
    OVER,
    PRESSED
};

class BasicWidget{
// Абстрактный класс для виджетов
public:
    BasicWidget()= default;
    virtual ~BasicWidget() = default;
    BasicWidget(BasicWidget& other) = delete;
    BasicWidget &operator=(BasicWidget const& other) = delete;
    BasicWidget(BasicWidget&& that) = delete;
    BasicWidget &operator=(BasicWidget&& that) = delete;
    friend void swap(BasicWidget& lhs, BasicWidget& rhs) = delete;

    // void set_focus(bool inp){focused = inp;};
    // void set_visible(bool inp){visible = inp;};
    // void set_active(bool inp){active = inp;};
    virtual void on_click_release(sf::RenderWindow* window, void* handler()) = 0;
    virtual void on_click_press(sf::RenderWindow* window) = 0;
    virtual void on_mouse_over(sf::RenderWindow* window) = 0;
    virtual void on_type() = 0;
    virtual void draw(sf::RenderWindow* window) const = 0;
    // sf::String get_data(){return data;};
    // void set_caption(sf::String inp) {caption.setString(inp);};
    // void set_hint(sf::String inp) {hint.setString(inp);};

protected:
    // bool focused;
    // mouseState clicked = FAR;
    // bool visible; 
    // bool active;
    // sf::Text caption;
    // sf::Text hint;
    // sf::Text data_box;
    // sf::String data;
    // int data_height;
    // int data_max_length;
    // sf::Texture background_image;
    // sf::Sprite background;
    // sf::Vector2f pos;
    // sf::Rect<float> active_zone;
    // sf::Vector2f scale_factor;



};

