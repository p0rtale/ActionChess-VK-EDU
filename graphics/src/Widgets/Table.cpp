#include <SFML/Graphics.hpp>
#include "Table.hpp"
#include "Variables.hpp"
#include <functional>
#include "Slidebar.hpp"
#include <MenuModel.hpp>




void Table::on_click_release(sf::RenderWindow* window){
    if(visible && active){
        slider.on_click_release(window);
    }
}
void Table::on_click_press(sf::RenderWindow* window) {
    if(visible && active){
        slider.on_click_press(window);
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (text_table.getGlobalBounds().contains(window->mapPixelToCoords(mouse_pos))) ? PRESSED : FAR;

        if(clicked == PRESSED){
            sf::Vector2f pos_on_texture(window->mapPixelToCoords(mouse_pos).x-text_table.getGlobalBounds().left,window->mapPixelToCoords(mouse_pos).y -text_table.getGlobalBounds().top + slider_offset);
            int last_selected = selected;
            int last_offset = selected_offset;
            for(int i=0;i<rooms_caption.size();i++){
                if(rooms_caption[i].getGlobalBounds().contains(pos_on_texture)){
                                                            
                    clicked_room = rooms[i];
                    handler();
                    break;
                }
                
            }
            
        }
    }
}
void Table::on_mouse_over(sf::RenderWindow* window){
    if(visible && active){
        slider.on_mouse_over(window);
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        clicked = (text_table.getGlobalBounds().contains(window->mapPixelToCoords(mouse_pos))) ? OVER : FAR;
        if(clicked == OVER){
            sf::Vector2f pos_on_texture(window->mapPixelToCoords(mouse_pos).x-text_table.getGlobalBounds().left,window->mapPixelToCoords(mouse_pos).y -text_table.getGlobalBounds().top + slider_offset);
            int last_selected = selected;
            int last_offset = selected_offset;
            for(int i=0;i<rooms_caption.size();i++){
                if(rooms_caption[i].getGlobalBounds().contains(pos_on_texture)){
                                                            
                    if(last_selected!= i){
                        selected_offset = 0;    
                    }
                    else{
                        selected_offset = last_offset;
                    }
                    selected = i;     
                }
                
            }
        }
        else {
            selected_offset = 0;
            std::cout<<rooms_caption.size()<<std::endl;
            if(((rooms_caption.size())>selected)){
                rooms_caption[selected].setPosition(0,rooms_caption[selected].getPosition().y);
            }

        }
        animate_click();
    }
}
void Table::on_type(sf::RenderWindow* window, sf::Event event){

}
void Table::draw(sf::RenderWindow* window) {
    if(visible){
        slider_offset = 0;
        if ((rooms_caption.size()*(caption.getGlobalBounds().height + 5) - text_zone.height*scale_factor.y)>=0){
            slider_offset = (rooms_caption.size()*(caption.getGlobalBounds().height + 10) - text_zone.height*scale_factor.y)*slider.get_pos();
        }
        text_table.setTextureRect(sf::IntRect(0,slider_offset,text_zone.width*scale_factor.x,text_zone.height*scale_factor.y)); //Исправить баг с последним

        render_texture();
        animate_click();
        
        table_texture.display();
        window->draw(background);
        slider.draw(window);
        window->draw(text_table);

    }
}

void Table::animate_click(){
    table_texture.clear(sf::Color(0,0,0,0));
    int s = rooms_caption.size();
    if((clicked == OVER)&&((s-1)>=selected)){
        sf::RectangleShape rect(sf::Vector2f(rooms_caption[selected].getGlobalBounds().width,rooms_caption[selected].getGlobalBounds().height));
        rect.setFillColor(sf::Color(150,150,255,50));
        rect.setPosition(rooms_caption[selected].getPosition());
        rect.move(0,5);
        table_texture.draw(rect);
        if(rooms_caption[selected].getGlobalBounds().width+selected_offset>text_table.getGlobalBounds().width){
            if (move_timer.getElapsedTime().asMicroseconds()>100){
                selected_offset -= 1;
                std::cout<<selected_offset<<std::endl;

                rooms_caption[selected].setPosition(selected_offset,rooms_caption[selected].getPosition().y);
                move_timer.restart();
            }
            else{
                selected_offset = 0;
            }
        }
        

    }
    for(int i=0;i<rooms_caption.size();i++){
                table_texture.draw(rooms_caption[i]);
            }
    
    
};
void Table::render_texture(){
    table_texture.clear(sf::Color(0,0,0,0));
    

    sf::Text temp = caption;
    float offset = temp.getGlobalBounds().height + 5;
    rooms_caption.clear();
    for(sf::String& i:rooms_str){
        rooms_caption.push_back(temp);
        rooms_caption.back().setString(i);     
        table_texture.draw(rooms_caption.back());
        temp.move(0,offset);
    }
    
    
};
void Table::set_rooms(std::vector<Rooms> inp_rooms){
    rooms = inp_rooms;
    parse_rooms();
}
void Table::parse_rooms(){
    rooms_str.clear();
    selected = 0;
    for(int i=0;i<rooms.size();i++){
        rooms_str.push_back(rooms[i].name + "  "+ std::to_string(rooms[i].users_num)+"/"+std::to_string(rooms[i].max_users_num));
    }
    render_texture();
};