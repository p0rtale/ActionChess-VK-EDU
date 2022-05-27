#include <SFML/Graphics.hpp>
#include "BasicWidget.hpp"
#include "Variables.hpp"
#include "Assets.hpp"
class Slidebar: public BasicWidget{
// Класс заполняемых тектовых полей
public:
    Slidebar(sf::Texture inp_slide_stick_im,sf::Texture inp_slider_im, sf::Vector2f inp_scale , sf::Vector2f inp_pos):slide_stick_image(inp_slide_stick_im),slider_image(inp_slider_im),scale_factor(inp_scale), pos(inp_pos){
                slide_stick.setTexture(slide_stick_image);
                slide_stick.setPosition(pos.x*scale_factor.x,pos.y*scale_factor.y);  
                sf::Rect<float> box = slide_stick.getGlobalBounds();

                slide_stick.setScale(scale_factor);

                slider.setTexture(slider_image);
                slider.setPosition(box.left+box.width/2-slider.getGlobalBounds().width/2,box.top);  
                slider.setScale(scale_factor);


            };
    
    Slidebar() {};
    ~Slidebar() {};

    void on_click_release(sf::RenderWindow* window)override;
    void on_click_press(sf::RenderWindow* window) override;
    void on_mouse_over(sf::RenderWindow* window)override;
    void on_type(sf::RenderWindow* window, sf::Event event)override;
    void draw(sf::RenderWindow* window) override;


protected:
    bool focused = false;
    mouseState clicked = FAR;
    bool visible = true; 
    bool active = true;
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