#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

static float beamRadius = 5;
static const int catchedBeamDistance = 10;
static const int catOrigin = 15;
//инициализируем фигуру указатель

struct FluffyCat
{
    sf::Texture texture;
    sf::Sprite sprite;
};

struct LaserBeam
{
    sf::CircleShape shape{beamRadius};
    sf::Vector2f position;
};

void initSprite(sf::Texture &texture, sf::Sprite &sprite)
{

    if (!texture.loadFromFile("cat.png"))
    {
        // error...
        std::cout << "OMG" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setOrigin({catOrigin, catOrigin});
}

void initBeam(LaserBeam &beam)
{
    beam.shape.setPosition({400, 300});
    beam.position = beam.shape.getPosition();
    beam.shape.setFillColor(sf::Color(0xFF, 0x0, 0x0));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
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

//Опрашивает и обрабатывает доступные события в цикле
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, sf::Vector2f &position)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            onMousePressed(event.mouseButton, position);
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

float length(const sf::Vector2f &vector)
{
    return std::hypot(vector.x, vector.y);
}

void moutionAnimation(sf::Vector2f delta, float deltaTime, sf::Sprite &sprite)
{
    const float maxArrowSpeed = 100.f;
    float deltaLength = length(delta);
    const sf::Vector2f directionMoution = sf::Vector2f{delta.x / deltaLength, delta.y / deltaLength};
    sf::Vector2f passedMoution = (maxArrowSpeed * deltaTime) * directionMoution;
    if (!(length(delta) < catchedBeamDistance))
    {
        sprite.setPosition(sprite.getPosition() + passedMoution);
    }
}

void checkSpriteScale(sf::Sprite &sprite, const sf::Vector2f &delta)
{
    if (delta.x < 0)
    {
        sprite.setScale(-1, 1);
    }
    else
    {
        sprite.setScale(1, 1);
    }
}

//Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::Sprite &sprite, sf::Clock &clock, LaserBeam &beam)
{
    beam.shape.setPosition(beam.position);
    const sf::Vector2f delta = beam.position - sprite.getPosition();
    checkSpriteScale(sprite, delta);
    const float deltaTime = clock.restart().asSeconds();
    const float angle = toDegrees(atan2(delta.y, delta.x));
    float currentAngleRotation = sprite.getRotation();
    float offsetAngle = rotationValue(currentAngleRotation, angle);
    if (beam.position != sprite.getPosition())
    {
        moutionAnimation(delta, deltaTime, sprite);
    }
    //std::cout << currentAngleRotation << std::endl;
}

//Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &sprite, sf::CircleShape &beam)
{
    window.clear(sf::Color::Green);
    window.draw(sprite);
    window.draw(beam);
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
        "Cat follows laser", sf::Style::Default, settings);

    FluffyCat cat;
    LaserBeam beam;
    sf::Vector2f mousePosition;

    initSprite(cat.texture, cat.sprite);
    initBeam(beam);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition, beam.position);
        update(mousePosition, cat.sprite, clock, beam);
        redrawFrame(window, cat.sprite, beam.shape);
    }
}