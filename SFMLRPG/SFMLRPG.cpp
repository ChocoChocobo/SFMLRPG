#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

// Структура пули, имеющая фигуру прямоугольника и флаг, говорящий о существовании объекта
struct Bullet
{
    CircleShape bulletShape;
    bool isDestroyed = false;
};
// Структура врага, имеющая фигуру прямоугольника и флаг, говорящий о существовании объекта
struct Enemy
{
    RectangleShape enemyShape;
    bool isDestroyed = false;
};

int main()
{    
    // Инициализация окна
    unsigned int width = 800;
    unsigned int height = 600;
    RenderWindow mainWindow(VideoMode({ width, height }), "RPO Invaders");

    // Инициализация игрока
    RectangleShape playerShape;
    playerShape.setSize({ 60.0f, 20.0f });
    playerShape.setFillColor(Color::Yellow);
    playerShape.setOutlineThickness(5.0f);
    playerShape.setOutlineColor(Color::Blue);
    playerShape.setOrigin({ 30.0f, 10.0f });
    playerShape.setPosition({ width / 2.0f, height - 10.0f });    

    // Инициализация других объектов
    std::vector<Bullet> bulletsArray;
    std::vector<Enemy> enemiesArray;
    // ...

    // Таймеры
    Clock framesClock; // используется для deltaTime
    Clock spawnEnemyClock;
    Clock spawnBulletClock;

    // Скорость объектов
    const float playerSpeed = 200.0f;
    const float enemySpeed = 175.0f;
    const float bulletSpeed = 400.0f;

    // Флаг конца игры
    bool isGameOver = false;

    while (mainWindow.isOpen() && !isGameOver)
    {        
        while (const std::optional event = mainWindow.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                mainWindow.close();
            }
        } 
        float playerDirection = 0.0f; // Направление игрока влево вправо
        // delta time - отношение кадра к предыдущему. Умножать на данное значение необходимо затем, чтобы количество кадров при разном количестве кадров в секунду, было одинаковым.
        float deltaTime = framesClock.restart().asSeconds();
        // Если нажата клавиша A или Стрелка влево, то изменяем направление движения фигуры игрока
        if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
            playerDirection -= 1.0f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
        {
            playerDirection += 1.0f;
        }
        playerShape.move({ playerDirection * playerSpeed * deltaTime, 0.0f });

        mainWindow.clear(Color(0, 0, 0, 255)); 

        mainWindow.draw(playerShape);
        mainWindow.display();
    }

    return 0;
}