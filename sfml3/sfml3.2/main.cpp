#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

static const int pupilRadius = 15;
static const int eyePointsCount = 200;
static const sf::Vector2f whiteRadius = {60.f, 140.f};

struct Eye
{
    sf::ConvexShape white;
    sf::CircleShape pupil{pupilRadius};
    sf::Vector2f position;
    sf::Vector2f pupilOffset;
};

struct Eyes
{
    Eye leftEye;
    Eye rightEye;
};

//Переводит полярные координаты в декартовы
sf::Vector2f toEuclidian(float radius, float angle)
{
    return {
        radius * std::cos(angle),
        radius * std::sin(angle)};
}

//Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180 / M_PI);
}

void onMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    //  std::cout << "mouse x=" << event.x << " mouse y=" << event.y << std::endl;
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

//Обновляет позицию и повороты частей стрелки согласно текущему состоянию стрелки
void updateEyeElements(Eye &eye)
{
    eye.white.setPosition(eye.position);
    eye.pupil.setPosition(eye.position + eye.pupilOffset);
}

// Инициализирует фигуру-стрелку
void initEye(Eye &eye)
{
    eye.white.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    eye.white.setPointCount(eyePointsCount);
    for (int pointNo = 0; pointNo < eyePointsCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(eyePointsCount);
        sf::Vector2f point = sf::Vector2f{
            whiteRadius.x * std::cos(angle),
            whiteRadius.y * std::sin(angle)};
        eye.white.setPoint(pointNo, point);
    }

    eye.pupil.setOrigin({pupilRadius, pupilRadius});
    eye.pupil.setFillColor(sf::Color(0x0, 0x0, 0x0));

    updateEyeElements(eye);
}

float length(const sf::Vector2f &mousePosition)
{
    return std::hypot(mousePosition.x, mousePosition.y);
}

float getVectorRotation(const sf::Vector2f &v)
{
    return atan2(v.y, v.x);
}

sf::Vector2f scaleY(const sf::Vector2f &v, float scale)
{
    return {v.x, v.y * scale};
}

sf::Vector2f getRealPosition(const sf::Vector2f &mousePosition, Eye &eye)
{
    const float scale = whiteRadius.x / whiteRadius.y;
    const sf::Vector2f mappedPosition = scaleY(eye.position, scale);
    const sf::Vector2f mappedMousePosition = scaleY(mousePosition, scale);
    const float angle = atan2(mappedMousePosition.y - mappedPosition.y, mappedMousePosition.x - mappedPosition.x);
    const sf::Vector2f orbitRadius = scaleY(whiteRadius - sf::Vector2f{pupilRadius, pupilRadius}, scale);
    const sf::Vector2f realPointOnVector = {
        (orbitRadius.x) * std::cos(angle),
        (orbitRadius.y) * std::sin(angle)};
    return scaleY(realPointOnVector, 1.0f / scale);
}

// Обновляет фигуру, указывающую на мышь
void updateEye(const sf::Vector2f &mousePosition, Eye &eye)
{
    const sf::Vector2f delta = mousePosition - eye.position;
    sf::Vector2f pupilOffset = getRealPosition(mousePosition, eye);
    if (length(delta) > length(pupilOffset))
    {
        eye.pupilOffset = pupilOffset;
    }
    else
    {
        eye.pupilOffset = delta;
    }
    std::cout << "Pupil offset = " << getVectorRotation(pupilOffset) << " "
              << "Delta offset = " << getVectorRotation(delta) << std::endl;
    updateEyeElements(eye);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eyes &eyes)
{
    window.clear();
    window.draw(eyes.leftEye.white);
    window.draw(eyes.leftEye.pupil);
    window.draw(eyes.rightEye.white);
    window.draw(eyes.rightEye.pupil);
    window.display();
}

void update(const sf::Vector2f &mousePosition, Eyes &eyes)
{
    updateEye(mousePosition, eyes.leftEye);
    updateEye(mousePosition, eyes.rightEye);
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eyes follows mouse", sf::Style::Default, settings);
    Eyes eyes;
    sf::Vector2f mousePosition;
    eyes.leftEye.position = {300, 300};
    eyes.rightEye.position = {500, 300};

    initEye(eyes.leftEye);
    initEye(eyes.rightEye);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eyes);
        redrawFrame(window, eyes);
    }
}