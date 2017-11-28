#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <cassert>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

constexpr unsigned maxNumberOfBalls = 10;
constexpr int maxColors = 8;

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
};

struct BallInputParametrs
{
    float radius;
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
    // return sf::Color(getRandomInt(generator, 0, 250), getRandomInt(generator, 0, 250), getRandomInt(generator, 0, 250));
}

void initBall(Ball (&ball)[maxNumberOfBalls], BallInputParametrs (&parametrs)[maxNumberOfBalls])
{
    PRNG generator;
    initGenerator(generator);

    for (int i = 0; i < maxNumberOfBalls; i++)
    {
        ball[i].shape.setRadius(parametrs[i].radius);
        ball[i].shape.setOrigin(parametrs[i].radius, parametrs[i].radius);
        ball[i].shape.setFillColor(setBallColor(generator));
        ball[i].shape.setPosition(parametrs[i].startPosition);
        ball[i].speed = setBallSpeed(generator);
    }
}

void getBallParametrs(BallInputParametrs (&array)[maxNumberOfBalls])
{
    array[0] = {40.f, sf::Vector2f{650, 300}};
    array[1] = {30.f, sf::Vector2f{200, 100}};
    array[2] = {20.f, sf::Vector2f{100, 200}};
    array[3] = {30.f, sf::Vector2f{400, 300}};
    array[4] = {15.f, sf::Vector2f{500, 500}};
    array[5] = {35.f, sf::Vector2f{600, 500}};
    array[6] = {25.f, sf::Vector2f{700, 400}};
    array[7] = {30.f, sf::Vector2f{250, 300}};
    array[8] = {20.f, sf::Vector2f{350, 200}};
    array[9] = {10.f, sf::Vector2f{460, 100}};
}

float length(const sf::Vector2f &vector)
{
    return std::hypot(vector.x, vector.y);
}

void checkBallsClash(Ball (&arrayOfBalls)[maxNumberOfBalls], const float deltaTime)
{
    for (int i = 0; i < maxNumberOfBalls; ++i)
    {
        for (int j = i + 1; j < maxNumberOfBalls; ++j)
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

void checkWallCrash(Ball (&arrayOfBalls)[maxNumberOfBalls], const float deltaTime)
{
    for (int i = 0; i < maxNumberOfBalls; i++)
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

void setBallNewPosition(Ball (&arrayOfBalls)[maxNumberOfBalls], sf::Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();

    checkBallsClash(arrayOfBalls, deltaTime);
    checkWallCrash(arrayOfBalls, deltaTime);
}

void drawBalls(Ball (&arrayOfBalls)[maxNumberOfBalls], sf::RenderWindow &window)
{
    for (int i = 0; i < maxNumberOfBalls; i++)
    {
        window.draw(arrayOfBalls[i].shape);
    }
}

int main()
{
    BallInputParametrs arrayOfBallsParams[maxNumberOfBalls];
    getBallParametrs(arrayOfBallsParams);

    Ball arrayOfBalls[maxNumberOfBalls];
    initBall(arrayOfBalls, arrayOfBallsParams);

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving ballZ");
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        setBallNewPosition(arrayOfBalls, clock);

        window.clear();
        drawBalls(arrayOfBalls, window);
        window.display();
    }
}