#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

constexpr unsigned maxNumberOfBalls = 10;

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
};

struct BallInputParametrs
{
    float radius;
    sf::Color color;
    sf::Vector2f startPosition;
    sf::Vector2f speed;
};

void initBall(Ball (&ball)[maxNumberOfBalls], BallInputParametrs (&parametrs)[maxNumberOfBalls])
{

    for (int i = 0; i < maxNumberOfBalls; i++)
    {
        ball[i].shape.setRadius(parametrs[i].radius);
        ball[i].shape.setFillColor(parametrs[i].color);
        ball[i].shape.setPosition(parametrs[i].startPosition);
        ball[i].speed = parametrs[i].speed;
    }
}

void getBallParametrs(BallInputParametrs (&array)[maxNumberOfBalls])
{
    array[0] = {40.f, sf::Color(0xFF, 0xFF, 0xFF), sf::Vector2f{300, 300}, sf::Vector2f{100.f, 150.f}};
    array[1] = {30.f, sf::Color(0xFF, 0xFF, 0x0), sf::Vector2f{200, 100}, sf::Vector2f{100.f, 250.f}};
    array[2] = {20.f, sf::Color(0xFF, 0x0, 0xFF), sf::Vector2f{100, 200}, sf::Vector2f{50.f, 150.f}};
    array[3] = {30.f, sf::Color(0xFF, 0x0, 0x0), sf::Vector2f{400, 300}, sf::Vector2f{100.f, 150.f}};
    array[4] = {15.f, sf::Color(0xAC, 0xF0, 0x1B), sf::Vector2f{500, 500}, sf::Vector2f{100.f, 250.f}};
    array[5] = {35.f, sf::Color(0xE2, 0x0, 0xA1), sf::Vector2f{600, 500}, sf::Vector2f{100.f, 350.f}};
    array[6] = {25.f, sf::Color(0xBC, 0xBC, 0xBC), sf::Vector2f{700, 400}, sf::Vector2f{100.f, 150.f}};
    array[7] = {30.f, sf::Color(0xA1, 0xA1, 0xA1), sf::Vector2f{250, 300}, sf::Vector2f{100.f, 50.f}};
    array[8] = {20.f, sf::Color(0xC1, 0x23, 0x23), sf::Vector2f{350, 200}, sf::Vector2f{100.f, 250.f}};
    array[9] = {10.f, sf::Color(0xFF, 0x0, 0x0), sf::Vector2f{460, 100}, sf::Vector2f{100.f, 50.f}};
}

void setBallNewPosition(Ball (&arrayOfBalls)[maxNumberOfBalls], sf::Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();

    for (int i = 0; i < maxNumberOfBalls; i++)
    {
        sf::Vector2f position = arrayOfBalls[i].shape.getPosition();
        position += arrayOfBalls[i].speed * deltaTime;

        if ((position.x + 2 * arrayOfBalls[i].shape.getRadius() >= WINDOW_WIDTH) && (arrayOfBalls[i].speed.x > 0))
        {
            arrayOfBalls[i].speed.x = -arrayOfBalls[i].speed.x;
        }
        if ((position.x < 0) && (arrayOfBalls[i].speed.x < 0))
        {
            arrayOfBalls[i].speed.x = -arrayOfBalls[i].speed.x;
        }
        if ((position.y + 2 * arrayOfBalls[i].shape.getRadius() >= WINDOW_HEIGHT) && (arrayOfBalls[i].speed.y > 0))
        {
            arrayOfBalls[i].speed.y = -arrayOfBalls[i].speed.y;
        }
        if ((position.y < 0) && (arrayOfBalls[i].speed.y < 0))
        {
            arrayOfBalls[i].speed.y = -arrayOfBalls[i].speed.y;
        }

        arrayOfBalls[i].shape.setPosition(position);
    }
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