#include "Engine.h"
 
Engine::Engine()
{
    // Получаем разрешение экрана, создаем окно SFML и View
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
 
    window.create(sf::VideoMode(resolution.x, resolution.y),
        "Dinamic chess",
        sf::Style::Fullscreen);
 
    // Загружаем фон в текстуру
    // Подготовьте изображение под ваш размер экрана в редакторе
    BackgroundTexture.loadFromFile("background.jpg");
 
    // Связываем спрайт и текстуру
    BackgroundSprite.setTexture(BackgroundTexture);


 
}

void Engine::update(float dtAsSeconds)
{
    figures.update(dtAsSeconds);
}

void Engine::draw()
{
    // Стираем предыдущий кадр
    window.clear(sf::Color::White);
 
    // Отрисовываем фон
    window.draw(BackgroundSprite);
    
    window.draw(board.getSprite());

    window.draw(board.get_rect());

    std::vector<sf::Sprite> Sprites = figures.getSprites(); 
    for (int i=0; i < Sprites.size();++i){
        window.draw(Sprites[i]);
    }
    // Отображаем все, что нарисовали
    window.display();
}
 
void Engine::start()
{
    // Расчет времени
    sf::Clock clock;
 
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
 
        update(dtAsSeconds);
        draw();
    }
}

