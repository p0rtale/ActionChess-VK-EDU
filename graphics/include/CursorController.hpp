#pragma once

#include <SFML/Graphics.hpp>


class CursorController{
    //Класс синглтон для оптимального управления курсором из классов виджетов
    //Работа класса такая: в начале цикла контроллера он делает reset на arrow, затем вызывается из виджетов, и если виджеты просят не arrow,то из draw выставляется курсор.
public:
    static CursorController& get_instance(){
        static CursorController Instance;
        return Instance;
    };
    void reset_cursor();
    void set_cursor(sf::Cursor::Type type);
    void draw_cursor(sf::RenderWindow* window);

private:
    sf::Cursor cursor;
    sf::Cursor::Type current_cursor_type = sf::Cursor::Arrow;
    sf::Cursor::Type cursor_type = sf::Cursor::Arrow;
    CursorController() = default;
    ~CursorController() = default;
    CursorController(CursorController const& other) = delete;
    CursorController &operator=(CursorController const& other) = delete;
    CursorController(CursorController&& that) = delete;
    CursorController &operator=(CursorController&& that) = delete;
    friend void swap(CursorController& lhs, CursorController& rhs) = delete;
    
};
