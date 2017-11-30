#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <cassert>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

constexpr int maxRadius = 40;
constexpr int minRadius = 15;
constexpr int maxColors = 8;
constexpr float maxBallLifeSpan = 10;
constexpr float ballDeathLimit = 0;

struct Ball
{
    sf::CircleShape shape;
    // int radius;
    sf::Vector2f speed;
    float span;
};

struct BallInputParametrs
{
    sf::Vector2f startPosition;
};

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

// Генерирует целое число в диапазоне [minValue, maxValue)
unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

// Генерирует число с плавающей точкой в диапазоне [minValue, maxValue)
float getRandomFloat(PRNG &generator, float minValue, float maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

int getRandomInt(PRNG &generator, int minValue, int maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

sf::Vector2f setBallSpeed(PRNG &generator)
{
    return sf::Vector2f(getRandomFloat(generator, -250.f, 250.f), getRandomFloat(generator, -250.f, 250.f));
}

void putColorsInArray(sf::Color (&array)[maxColors])
{
    array[0] = sf::Color(255, 255, 255);
    array[1] = sf::Color(255, 0, 0);
    array[2] = sf::Color(0, 255, 0);
    array[3] = sf::Color(0, 0, 255);
    array[4] = sf::Color(255, 255, 0);
    array[5] = sf::Color(0, 255, 255);
    array[6] = sf::Color(0, 0, 0);
    array[7] = sf::Color(255, 0, 255);
}

sf::Color setBallColor(PRNG &generator)
{

    sf::Color arrayBallColors[maxColors];
    // size_t size = sizeof(arrayBallColors) / sizeof(arrayBallColors[0]);
    // std::cout << size << std::endl;

    putColorsInArray(arrayBallColors);

    sf::Color firstColor = arrayBallColors[getRandomInt(generator, 0, maxColors - 1)];
    sf::Color secondColor = arrayBallColors[getRandomInt(generator, 0, maxColors - 1)];

    int newRed = (firstColor.r + secondColor.r) / 2;
    int newGreen = (firstColor.g + secondColor.g) / 2;
    int newBlue = (firstColor.b + secondColor.b) / 2;

    return sf::Color(newRed, newGreen, newBlue);
}

void initBall(std::vector<Ball> &ball, PRNG &generator, sf::Vector2f &startPosition)
{
    Ball newBall;
    // newBall.radius = getRandomInt(generator, minRadius, maxRadius);

    newBall.shape.setRadius(getRandomInt(generator, minRadius, maxRadius));
    newBall.shape.setOrigin(newBall.shape.getRadius(), newBall.shape.getRadius());
    newBall.shape.setFillColor(setBallColor(generator));
    newBall.shape.setPosition(startPosition);
    newBall.speed = setBallSpeed(generator);
    newBall.span = maxBallLifeSpan;

    ball.push_back(newBall);
}

float length(const sf::Vector2f &vector)
{
    return std::hypot(vector.x, vector.y);
}

bool checkNewBallPosition(std::vector<Ball> &ball, sf::Vector2f &startPosition)
{
    bool result = true;

    for (int i = 0; i < ball.size(); ++i)
    {
        if (length(ball[i].shape.getPosition() - startPosition) < (2 * maxRadius)) //ball[i].shape.getRadius()
            result = false;
    }

    return result;
}

void checkBallsClash(std::vector<Ball> &arrayOfBalls, const float deltaTime)
{
    for (int i = 0; i < arrayOfBalls.size(); ++i)
    {
        for (int j = i + 1; j < arrayOfBalls.size(); ++j)
        {
            if (length(arrayOfBalls[i].shape.getPosition() - arrayOfBalls[j].shape.getPosition()) <= (arrayOfBalls[i].shape.getRadius() + arrayOfBalls[j].shape.getRadius()))
            {

                sf::Vector2f deltaI = arrayOfBalls[i].shape.getPosition() - arrayOfBalls[j].shape.getPosition();
                sf::Vector2f speedI = arrayOfBalls[i].speed - arrayOfBalls[j].speed;
                float scalarSpeedDeltaI = speedI.x * deltaI.x + speedI.y * deltaI.y;
                float scalarDeltaI = deltaI.x * deltaI.x + deltaI.y * deltaI.y;

                sf::Vector2f deltaJ = arrayOfBalls[j].shape.getPosition() - arrayOfBalls[i].shape.getPosition();
                sf::Vector2f speedJ = arrayOfBalls[j].speed - arrayOfBalls[i].speed;
                float scalarSpeedDeltaJ = speedJ.x * deltaJ.x + speedJ.y * deltaJ.y;
                float scalarDeltaJ = deltaJ.x * deltaJ.x + deltaJ.y * deltaJ.y;

                arrayOfBalls[i].speed = arrayOfBalls[i].speed - (scalarSpeedDeltaI / scalarDeltaI) * deltaI;
                arrayOfBalls[j].speed = arrayOfBalls[j].speed - (scalarSpeedDeltaJ / scalarDeltaJ) * deltaJ;
            }
        }
    }
}

void checkWallCrash(std::vector<Ball> &arrayOfBalls, const float deltaTime)
{
    for (int i = 0; i < arrayOfBalls.size(); i++)
    {
        sf::Vector2f position = arrayOfBalls[i].shape.getPosition();
        const float radius = arrayOfBalls[i].shape.getRadius();
        position += arrayOfBalls[i].speed * deltaTime;

        if ((position.x - radius + 2 * radius >= WINDOW_WIDTH) && (arrayOfBalls[i].speed.x > 0))
        {
            arrayOfBalls[i].speed.x = -arrayOfBalls[i].speed.x;
        }
        if ((position.x - radius < 0) && (arrayOfBalls[i].speed.x < 0))
        {
            arrayOfBalls[i].speed.x = -arrayOfBalls[i].speed.x;
        }
        if ((position.y - radius + 2 * radius >= WINDOW_HEIGHT) && (arrayOfBalls[i].speed.y > 0))
        {
            arrayOfBalls[i].speed.y = -arrayOfBalls[i].speed.y;
        }
        if ((position.y - radius < 0) && (arrayOfBalls[i].speed.y < 0))
        {
            arrayOfBalls[i].speed.y = -arrayOfBalls[i].speed.y;
        }

        arrayOfBalls[i].shape.setPosition(position);
    }
}

// void updateBallRadius(std::vector<Ball> &arrayOfBalls, const float deltaTime)
// {
//     for (int i = 0; i < arrayOfBalls.size(); i++)
//     {
//         if (arrayOfBalls[i].radius > arrayOfBalls[i].shape.getRadius())
//         {
//             arrayOfBalls[i].shape.setRadius(arrayOfBalls[i].shape.getRadius() + 1);
//             arrayOfBalls[i].shape.setOrigin(arrayOfBalls[i].shape.getRadius(), arrayOfBalls[i].shape.getRadius());
//         }
//     }
// }

void updateBallLifetime(std::vector<Ball> &arrayOfBalls, const float deltaTime)
{
    for (int i = 0; i < arrayOfBalls.size(); i++)
    {
        arrayOfBalls[i].span = arrayOfBalls[i].span - deltaTime;
    }
}

void changeBallLifeSpan(std::vector<Ball> &arrayOfBalls, const float deltaTime)
{
    arrayOfBalls.erase(std::remove_if(arrayOfBalls.begin(), arrayOfBalls.end(),
                                      [](Ball const &ball) { return ball.span < ballDeathLimit; }),
                       arrayOfBalls.end());
    updateBallLifetime(arrayOfBalls, deltaTime);
}

void setBallNewPosition(std::vector<Ball> &arrayOfBalls, sf::Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();
    const float deltaMiniTime = deltaTime / arrayOfBalls.size();
    // changeBallLifeSpan(arrayOfBalls, deltaTime);
    for (int i = 0; i < arrayOfBalls.size(); i++)
    {
        checkBallsClash(arrayOfBalls, deltaMiniTime);
        checkWallCrash(arrayOfBalls, deltaMiniTime);
    }
}

void drawBalls(std::vector<Ball> &arrayOfBalls, sf::RenderWindow &window)
{
    window.clear();
    for (int i = 0; i < arrayOfBalls.size(); i++)
    {
        window.draw(arrayOfBalls[i].shape);
    }
    window.display();
}

void onMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    // std::cout << "mouse x=" << event.x << "mouse y=" << event.y << std::endl;
    mousePosition = {float(event.x),
                     float(event.y)};
}

void onMousePressed(sf::Event::MouseButtonEvent &event, sf::Vector2f &position)
{
    std::cout << "Pressed mouse x=" << event.x << "mouse y=" << event.y << std::endl;
    position = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, std::vector<Ball> &arrayOfBalls, sf::Vector2f &mousePosition)
{
    sf::Event event;
    sf::Vector2f position;

    PRNG generator;
    initGenerator(generator);

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            onMousePressed(event.mouseButton, position);
            if (checkNewBallPosition(arrayOfBalls, position))
                initBall(arrayOfBalls, generator, position);
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

int main()
{
    std::vector<Ball> arrayOfBalls;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving ballZ");
    sf::Clock clock;
    sf::Vector2f mousePosition;

    while (window.isOpen())
    {

        pollEvents(window, arrayOfBalls, mousePosition);
        setBallNewPosition(arrayOfBalls, clock);
        drawBalls(arrayOfBalls, window);
    }
}