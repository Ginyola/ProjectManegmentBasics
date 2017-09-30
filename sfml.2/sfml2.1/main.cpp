#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

int main()
{
    sf::Vector2f speed = {100.f, 50.f};
    constexpr float BALL_SIZE = 40;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving ball");
    sf::Clock clockX;
    sf::Clock clockY;

    sf::CircleShape shape(BALL_SIZE);
    const sf::Vector2f startPosition = {10, 350};
    sf::Vector2f offset = {0, 0};
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

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

        const float deltaTimeX = clockX.restart().asSeconds();
        constexpr float periodY = 2;
        const float TimeY = clockY.getElapsedTime().asSeconds();
        const float wavePhase = TimeY * float(2 * M_PI);
        // sf::Vector2f offset = shape.getPosition();
        // speed.y = speed.y * std::sin(wavePhase / periodY);
        offset.x += speed.x * deltaTimeX;
        offset.y = speed.y * std::sin(wavePhase / periodY);
        sf::Vector2f position = startPosition + offset;

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0))
        {
            speed.y = -speed.y;
        }
        if ((position.y < 0) && (speed.y < 0))
        {
            speed.y = -speed.y;
        }

        shape.setPosition(position);

        window.clear();
        window.draw(shape);
        window.display();
    }
}