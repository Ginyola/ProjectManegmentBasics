#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
const float moutionRadius = 100;
const float moutionSpeed = 100;

int main()
{
    constexpr int pointCount = 200;
    sf::Vector2f ellipseRadius = {0, 0};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Ellipse",
        sf::Style::Default, settings);

    sf::Clock clock;
    sf::ConvexShape ellipse;

    ellipse.setPosition({400, 300});
    ellipse.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        ellipseRadius.x = 200 * std::sin(6 * angle);
        ellipseRadius.y = 200 * std::sin(6 * angle);
        sf::Vector2f point = sf::Vector2f{
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

    sf::Vector2f position = ellipse.getPosition();

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

        // constexpr float speedX = 100.f;
        // constexpr float amplitudeY = 80.f;
        // constexpr float periodY = 2;

        const float time = clock.getElapsedTime().asSeconds();
        float moutionAngle = (moutionSpeed * time) / moutionRadius;
        // const float wavePhase = time * float(2 * M_PI);
        const float x = moutionRadius * std::cos(moutionAngle);
        const float y = moutionRadius * std::sin(moutionAngle);
        const sf::Vector2f offset = {x, y};

        ellipse.setPosition(position + offset);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}