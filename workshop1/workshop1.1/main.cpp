#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Arrow
{
    sf::ConvexShape shape;
    sf::Vector2f position;
    float rotation = 0;
};

//инициализируем фигуру указатель
void init(Arrow &arrow)
{
    arrow.position = {400, 300};

    arrow.shape.setPointCount(7);
    arrow.shape.setPoint(0, {55, 0});
    arrow.shape.setPoint(1, {0, -55});
    arrow.shape.setPoint(2, {0, -35});
    arrow.shape.setPoint(3, {-50, -35});
    arrow.shape.setPoint(4, {-50, 35});
    arrow.shape.setPoint(5, {0, 35});
    arrow.shape.setPoint(6, {0, 55});
    arrow.shape.setPosition(arrow.position);
    arrow.shape.setFillColor(sf::Color(0xFF, 0xFF, 0));
    arrow.shape.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    arrow.shape.setOutlineThickness(5.f);
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

float length(const sf::Vector2f &vector)
{
    return std::hypot(vector.x, vector.y);
}

void moutionAnimation(sf::Vector2f delta, float deltaTime, sf::ConvexShape &pointer)
{
    const float maxArrowSpeed = 50.f;
    float deltaLength = length(delta);
    const sf::Vector2f directionMoution = sf::Vector2f{delta.x / deltaLength, delta.y / deltaLength};
    sf::Vector2f passedMoution = (maxArrowSpeed * deltaTime) * directionMoution;
    if (length(delta) < length(passedMoution))
    {
        passedMoution = delta;
    }

    pointer.setPosition(pointer.getPosition() + passedMoution);
}

//Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float deltaTime = clock.restart().asSeconds();
    const float angle = toDegrees(atan2(delta.y, delta.x));
    float currentAngleRotation = pointer.getRotation();
    float offsetAngle = rotationValue(currentAngleRotation, angle);
    if (mousePosition != pointer.getPosition())
    {
        rotationAnimation(offsetAngle, deltaTime, pointer);
        moutionAnimation(delta, deltaTime, pointer);
    }
    std::cout << currentAngleRotation << std::endl;
}

//Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color::White);
    window.draw(pointer);
    window.display();
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

    Arrow arrow;
    sf::Vector2f mousePosition;

    init(arrow);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, arrow.shape, clock);
        redrawFrame(window, arrow.shape);
    }
}