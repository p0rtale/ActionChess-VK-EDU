#include "CursorController.hpp"
#include <SFML/Graphics.hpp>


void CursorController::reset_cursor(){
    cursor_type = sf::Cursor::Type::Arrow;
}

void CursorController::set_cursor(sf::Cursor::Type type){
    cursor_type = type;
}

void CursorController::draw_cursor(sf::RenderWindow* window){
    if (current_cursor_type != cursor_type){
        current_cursor_type = cursor_type;
        
        if (cursor.loadFromSystem(current_cursor_type)){
            window->setMouseCursor(cursor);
        }
        else{
            //TODO: добавить обработку этого исключения
        }
    }
}