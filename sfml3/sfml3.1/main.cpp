#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

//инициализируем фигуру указатель
void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << "mouse y=" << event.y << std::endl;
    mousePosition = {float(event.x),
                     float(event.y)};
}

//Опрашивает и обрабатывает доступные события в цикле
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

//Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

//плавное вращение?
//#error do not use out-parameter
float rotationValue(float &currentAngleRotation, const float &angle)
{
    constexpr float maxValue = 360.f;
    const float valueAngle = fmodf(angle + maxValue, maxValue);
    //std::cout << valueAngle << std::endl;
    currentAngleRotation = valueAngle - currentAngleRotation;
    if (currentAngleRotation < 0)
    {
        currentAngleRotation = currentAngleRotation + 360.f;
    }

    return currentAngleRotation;
}

void rotationAnimation(float offsetAngle, float deltaTime, sf::ConvexShape &pointer)
{
    std::cout << "offsetAngle=" << offsetAngle << std::endl;
    float tempRotation = offsetAngle;
    const float rotationSpeed = 150.f;
    float rotationAngle = 0;

    if (tempRotation < 180)
    {
        rotationAngle = std::min(tempRotation, deltaTime * rotationSpeed);
    }
    else
    {
        rotationAngle = std::min(tempRotation, -deltaTime * rotationSpeed);
    }
    pointer.setRotation(pointer.getRotation() + rotationAngle);
}

//Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float deltaTime = clock.restart().asSeconds();
    const float angle = toDegrees(atan2(delta.y, delta.x));
    float currentAngleRotation = pointer.getRotation();
    float offsetAngle = rotationValue(currentAngleRotation, angle);
    rotationAnimation(offsetAngle, deltaTime, pointer);
    std::cout << currentAngleRotation << std::endl;
    //pointer.setRotation(angle);
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Clock clock;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, clock);
        redrawFrame(window, pointer);
    }
}