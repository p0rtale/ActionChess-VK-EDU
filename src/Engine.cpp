#include "Engine.hpp"
 
Engine::Engine()
{
    // Получаем разрешение экрана, создаем окно SFML и View

    //resolution.x = sf::VideoMode::getDesktopMode().width;
    //resolution.y = sf::VideoMode::getDesktopMode().height;
    resolution.x = 1280;
    resolution.y = 720;
    
    window.create(sf::VideoMode(resolution.x, resolution.y),
        "Active chess",sf::Style::Close);
 
    // Загружаем фон в текстуру
    m_BackgroundTexture.loadFromFile("images/background.jpg");
 
    // Связываем спрайт и текстуру
    m_BackgroundSprite.setTexture(m_BackgroundTexture);

    // выстовка по координатам спрайта
    m_BackgroundSprite.setPosition(0,0);

    float WidgetWidth = (float) resolution.x / (float) m_BackgroundTexture.getSize().x;
    float WidgetHeight = (float) resolution.y / (float) m_BackgroundTexture.getSize().y;
    m_BackgroundSprite.setScale(WidgetWidth, WidgetHeight);
    
    // response цвет
    board = std::make_shared<BoardTable>(resolution);
    player_figures = std::make_shared<GroupFigure>(resolution,true,'w');
    opponent_figures = std::make_shared<GroupFigure>(resolution,false,'b');
}

Engine::~Engine(){}

void Engine::update(sf::Event event)
{
    //response delete и move
    player_figures->update(event,&window,board);
    opponent_figures->update(event,&window,board);
}
void Engine::draw()
{
    // Стираем предыдущий кадр
    window.clear(sf::Color::White);

    // Отрисовываем фон
    window.draw(m_BackgroundSprite);

    board->draw(&window);
    
    player_figures->draw(&window);

    opponent_figures->draw(&window);
    
    // Отображаем все, что нарисовали
    window.display();
}
 
void Engine::start()
{
    // Игровой цикл
    while (window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        // Перезапускаем таймер и записываем отмеренное время в dt
       // sf::Time dt = clock.restart();
 
       // float dtAsSeconds = dt.asSeconds();
      //  update(event);
        draw();
    }
}



