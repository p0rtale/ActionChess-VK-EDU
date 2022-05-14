#include "Engine.hpp"
 
Engine::Engine()
{
    // Получаем разрешение экрана, создаем окно SFML и View

    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
    
    window.create(sf::VideoMode(resolution.x, resolution.y),
        "Dinamic chess",
        sf::Style::Fullscreen);
 
    // Загружаем фон в текстуру
    m_BackgroundTexture.loadFromFile("background.jpg");
 
    // Связываем спрайт и текстуру
    m_BackgroundSprite.setTexture(m_BackgroundTexture);

    board = new BoardTable(resolution);
    player_figures = new GroupFigure(resolution,true,'w');
    opponent_figures = new GroupFigure(resolution,false,'b');
}

Engine::~Engine(){
    delete[] board;
    delete[] player_figures;
    delete[] opponent_figures;
}

void Engine::update(float dtAsSeconds,sf::Event event)
{
    player_figures->update(event,window,*board);
    opponent_figures->update(event,window,*board);
}

void Engine::draw()
{
    // Стираем предыдущий кадр
    window.clear(sf::Color::White);
 
    // Отрисовываем фон
    window.draw(m_BackgroundSprite);
    
    std::vector<sf::Sprite> cage_figures = board->getSprites(); 
    for (int i=0; i < cage_figures.size();++i){
        window.draw(cage_figures[i]);
    }
    std::vector<sf::Sprite> pl_figures = player_figures->getSprites(); 
    for (int i=0; i < pl_figures.size();++i){
        window.draw(pl_figures[i]);
    }
    std::vector<sf::Sprite> op_figures = opponent_figures->getSprites(); 
    for (int i=0; i < op_figures.size();++i){
        window.draw(op_figures[i]);
    }
    // Отображаем все, что нарисовали
    window.display();
}
 
void Engine::start()
{
    // Расчет времени
    sf::Clock clock;
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
        sf::Time dt = clock.restart();
 
        float dtAsSeconds = dt.asSeconds();
        update(dtAsSeconds,event);
        draw();
    }
}



