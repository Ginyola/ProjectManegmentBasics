#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

int main()
{
    sf::ConvexShape trinagle;
    trinagle.setFillColor(sf::Color(0xFF, 0x80, 0x0));
    trinagle.setPosition({200, 120});
    trinagle.setPointCount(3);
    trinagle.setPoint(0, {50, -20});
    trinagle.setPoint(1, {50, 20});
    trinagle.setPoint(2, {-100, 0});

    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    trapeze.setPosition({400, 300});
    trapeze.setPointCount(4);
    trapeze.setPoint(0, {-90, 0});
    trapeze.setPoint(1, {+90, 0});
    trapeze.setPoint(2, {+120, 60});
    trapeze.setPoint(3, {-120, 60});

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Convex Shape");
    window.clear();
    window.draw(trinagle);
    window.draw(trapeze);
    window.display();

    sf::sleep(sf::seconds(5));
}