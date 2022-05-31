#pragma once 


#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "BasicStage.hpp"
#include "Client.hpp"

class WindowSwitcher{ 
/* Глобальный контроллер приложения, синглтон Имеет в себе указатель
// на класс конкретного окна (меню, игра и тд),
//при смене окна, окно возвращзает ссылкой экземпляр следующего окна
*/
public:
    static WindowSwitcher&  get_instance(){
        static WindowSwitcher instance;
        return instance;
    }
    void init(Client* inp_c);
    void run();
private:
    sf::RenderWindow* window;
    std::string window_head_name = "Action Chess";
    BasicStage* Stage;
    WindowSwitcher() = default;
    ~WindowSwitcher();
    WindowSwitcher(WindowSwitcher const& other) = delete;
    WindowSwitcher &operator=(WindowSwitcher const& other) = delete;
    WindowSwitcher(WindowSwitcher&& that) = delete;
    WindowSwitcher &operator=(WindowSwitcher&& that) = delete;
    friend void swap(WindowSwitcher& lhs, WindowSwitcher& rhs) = delete;
    Client* c;
};
