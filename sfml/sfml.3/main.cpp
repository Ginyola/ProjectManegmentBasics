#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({480, 500}), "House");
    window.clear();

    sf::RectangleShape walls;
    walls.setPosition({60, 280});
    walls.setSize({360, 200});
    walls.setFillColor(sf::Color(0xB3, 0x59, 0x0));

    sf::RectangleShape door;
    door.setPosition({100, 340});
    door.setSize({60, 140});
    //shape1.setRotation(75);
    door.setFillColor(sf::Color(0x33, 0x33, 0x33));

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(0x7A, 0x1F, 0x1F));
    roof.setPosition({20, 280});
    roof.setPointCount(4);
    roof.setPoint(0, {0, 0});
    roof.setPoint(1, {100, -80});
    roof.setPoint(2, {340, -80});
    roof.setPoint(3, {440, 0});

    sf::RectangleShape pipe1;
    pipe1.setPosition({300, 180});
    pipe1.setSize({30, 60});
    pipe1.setFillColor(sf::Color(0x2E, 0x2E, 0x2E));

    sf::RectangleShape pipe2;
    pipe2.setPosition({284, 140});
    pipe2.setSize({60, 40});
    pipe2.setFillColor(sf::Color(0x2E, 0x2E, 0x2E));

    sf::CircleShape smoke1(16);
    smoke1.setPosition({310, 110});
    smoke1.setFillColor(sf::Color(0xCB, 0xCB, 0xCB));
    window.draw(smoke1);

    sf::CircleShape smoke2(20);
    smoke2.setPosition({320, 80});
    smoke2.setFillColor(sf::Color(0xCB, 0xCB, 0xCB));
    window.draw(smoke2);

    sf::CircleShape smoke3(26);
    smoke3.setPosition({340, 46});
    smoke3.setFillColor(sf::Color(0xCB, 0xCB, 0xCB));
    window.draw(smoke3);

    sf::CircleShape smoke4(32);
    smoke4.setPosition({360, 10});
    smoke4.setFillColor(sf::Color(0xCB, 0xCB, 0xCB));
    window.draw(smoke4);

    window.draw(walls);
    window.draw(door);
    window.draw(roof);
    window.draw(smoke1);
    window.draw(smoke2);
    // window.draw(smoke3);
    // window.draw(smoke4);
    window.draw(pipe1);
    window.draw(pipe2);

    window.display();

    sf::sleep(sf::seconds(5));
}