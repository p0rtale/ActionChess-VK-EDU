#pragma once

#include <SFML/Graphics.hpp>

class BasicWindow
{

public:
    virtual BasicWindow* event_handler();
    void init();
    BasicWindow& get_instance();
    virtual void draw();
    void set_active(){active = true;}
    void set_inactive(){active = false;}
private:
    BasicWindow();
    ~BasicWindow();
    BasicWindow(BasicWindow const& other) = delete;
    BasicWindow &operator=(BasicWindow const& other) = delete;
    BasicWindow(BasicWindow&& that) = delete;
    BasicWindow &operator=(BasicWindow&& that) = delete;
    friend void swap(BasicWindow& lhs, BasicWindow& rhs) = delete;
 

    sf::Texture background_image;
    sf::Sprite background;
    std::string window_head_name = "untitled";
    sf::Font font;
    sf::Vector2f size;
    bool visible;
    bool active;
    std::vector<sf::Sprite> sprites;
};

