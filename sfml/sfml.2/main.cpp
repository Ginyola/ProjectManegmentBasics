#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

int main()
{
    sf::ConvexShape firstLetter_1;
    firstLetter_1.setFillColor(sf::Color(0xAF, 0x40, 0x0));
    firstLetter_1.setPosition({50, 50});
    firstLetter_1.setPointCount(4);
    firstLetter_1.setPoint(0, {0, 0});
    firstLetter_1.setPoint(1, {200, 0});
    firstLetter_1.setPoint(2, {200, 50});
    firstLetter_1.setPoint(3, {0, 50});

    sf::ConvexShape firstLetter_2;
    firstLetter_2.setFillColor(sf::Color(0xAF, 0x40, 0x0));
    firstLetter_2.setPosition({50, 50});
    firstLetter_2.setPointCount(4);
    firstLetter_2.setPoint(0, {0, 0});
    firstLetter_2.setPoint(1, {0, 350});
    firstLetter_2.setPoint(2, {50, 350});
    firstLetter_2.setPoint(3, {50, 0});

    sf::ConvexShape firstLetter_3;
    firstLetter_3.setFillColor(sf::Color(0xAF, 0x40, 0x0));
    firstLetter_3.setPosition({50, 50});
    firstLetter_3.setPointCount(4);
    firstLetter_3.setPoint(0, {200, 0});
    firstLetter_3.setPoint(1, {200, 100});
    firstLetter_3.setPoint(2, {150, 100});
    firstLetter_3.setPoint(3, {150, 0});

    sf::ConvexShape firstLetter_4;
    firstLetter_4.setFillColor(sf::Color(0xAF, 0x40, 0x0));
    firstLetter_4.setPosition({50, 50});
    firstLetter_4.setPointCount(4);
    firstLetter_4.setPoint(0, {0, 350});
    firstLetter_4.setPoint(1, {200, 350});
    firstLetter_4.setPoint(2, {200, 300});
    firstLetter_4.setPoint(3, {0, 300});

    sf::ConvexShape firstLetter_5;
    firstLetter_5.setFillColor(sf::Color(0xAF, 0x40, 0x0));
    firstLetter_5.setPosition({50, 50});
    firstLetter_5.setPointCount(4);
    firstLetter_5.setPoint(0, {100, 150});
    firstLetter_5.setPoint(1, {100, 200});
    firstLetter_5.setPoint(2, {200, 200});
    firstLetter_5.setPoint(3, {200, 150});

    sf::ConvexShape firstLetter_6;
    firstLetter_6.setFillColor(sf::Color(0xAF, 0x40, 0x0));
    firstLetter_6.setPosition({50, 50});
    firstLetter_6.setPointCount(4);
    firstLetter_6.setPoint(0, {150, 200});
    firstLetter_6.setPoint(1, {200, 200});
    firstLetter_6.setPoint(2, {200, 350});
    firstLetter_6.setPoint(3, {150, 350});

    sf::ConvexShape secondLetter_1;
    secondLetter_1.setFillColor(sf::Color(0x0, 0x40, 0xFF));
    secondLetter_1.setPosition({300, 50});
    secondLetter_1.setPointCount(4);
    secondLetter_1.setPoint(0, {0, 0});
    secondLetter_1.setPoint(1, {50, 0});
    secondLetter_1.setPoint(2, {50, 350});
    secondLetter_1.setPoint(3, {0, 350});

    sf::ConvexShape secondLetter_2;
    secondLetter_2.setFillColor(sf::Color(0x0, 0x40, 0xFF));
    secondLetter_2.setPosition({300, 50});
    secondLetter_2.setPointCount(4);
    secondLetter_2.setPoint(0, {50, 105});
    secondLetter_2.setPoint(1, {135, 0});
    secondLetter_2.setPoint(2, {190, 0});
    secondLetter_2.setPoint(3, {50, 170});

    sf::ConvexShape secondLetter_3;
    secondLetter_3.setFillColor(sf::Color(0x0, 0x40, 0xFF));
    secondLetter_3.setPosition({300, 50});
    secondLetter_3.setPointCount(4);
    secondLetter_3.setPoint(0, {50, 120});
    secondLetter_3.setPoint(1, {50, 210});
    secondLetter_3.setPoint(2, {145, 350});
    secondLetter_3.setPoint(3, {200, 350});

    sf::ConvexShape thirdLetter_1;
    thirdLetter_1.setFillColor(sf::Color(0x0, 0xFF, 0x3F));
    thirdLetter_1.setPosition({550, 50});
    thirdLetter_1.setPointCount(4);
    thirdLetter_1.setPoint(0, {0, 0});
    thirdLetter_1.setPoint(1, {0, 50});
    thirdLetter_1.setPoint(2, {200, 50});
    thirdLetter_1.setPoint(3, {200, 0});

    sf::ConvexShape thirdLetter_2;
    thirdLetter_2.setFillColor(sf::Color(0x0, 0xFF, 0x3F));
    thirdLetter_2.setPosition({550, 50});
    thirdLetter_2.setPointCount(4);
    thirdLetter_2.setPoint(0, {150, 0});
    thirdLetter_2.setPoint(1, {200, 0});
    thirdLetter_2.setPoint(2, {200, 100});
    thirdLetter_2.setPoint(3, {150, 100});

    sf::ConvexShape thirdLetter_3;
    thirdLetter_3.setFillColor(sf::Color(0x0, 0xFF, 0x3F));
    thirdLetter_3.setPosition({550, 50});
    thirdLetter_3.setPointCount(4);
    thirdLetter_3.setPoint(0, {0, 0});
    thirdLetter_3.setPoint(1, {50, 0});
    thirdLetter_3.setPoint(2, {50, 200});
    thirdLetter_3.setPoint(3, {0, 200});

    sf::ConvexShape thirdLetter_4;
    thirdLetter_4.setFillColor(sf::Color(0x0, 0xFF, 0x3F));
    thirdLetter_4.setPosition({550, 50});
    thirdLetter_4.setPointCount(4);
    thirdLetter_4.setPoint(0, {0, 150});
    thirdLetter_4.setPoint(1, {0, 200});
    thirdLetter_4.setPoint(2, {200, 200});
    thirdLetter_4.setPoint(3, {200, 150});

    sf::ConvexShape thirdLetter_5;
    thirdLetter_5.setFillColor(sf::Color(0x0, 0xFF, 0x3F));
    thirdLetter_5.setPosition({550, 50});
    thirdLetter_5.setPointCount(4);
    thirdLetter_5.setPoint(0, {200, 150});
    thirdLetter_5.setPoint(1, {150, 150});
    thirdLetter_5.setPoint(2, {150, 350});
    thirdLetter_5.setPoint(3, {200, 350});

    sf::ConvexShape thirdLetter_6;
    thirdLetter_6.setFillColor(sf::Color(0x0, 0xFF, 0x3F));
    thirdLetter_6.setPosition({550, 50});
    thirdLetter_6.setPointCount(4);
    thirdLetter_6.setPoint(0, {200, 300});
    thirdLetter_6.setPoint(1, {200, 350});
    thirdLetter_6.setPoint(2, {0, 350});
    thirdLetter_6.setPoint(3, {0, 300});

    sf::ConvexShape thirdLetter_7;
    thirdLetter_7.setFillColor(sf::Color(0x0, 0xFF, 0x3F));
    thirdLetter_7.setPosition({550, 50});
    thirdLetter_7.setPointCount(4);
    thirdLetter_7.setPoint(0, {0, 350});
    thirdLetter_7.setPoint(1, {50, 350});
    thirdLetter_7.setPoint(2, {50, 250});
    thirdLetter_7.setPoint(3, {0, 250});

    sf::RenderWindow window(sf::VideoMode({800, 450}), "Convex Shape");
    window.clear();

    window.draw(firstLetter_1);
    window.draw(firstLetter_2);
    window.draw(firstLetter_3);
    window.draw(firstLetter_4);
    window.draw(firstLetter_5);
    window.draw(firstLetter_6);

    window.draw(secondLetter_1);
    window.draw(secondLetter_2);
    window.draw(secondLetter_3);

    window.draw(thirdLetter_1);
    window.draw(thirdLetter_2);
    window.draw(thirdLetter_3);
    window.draw(thirdLetter_4);
    window.draw(thirdLetter_5);
    window.draw(thirdLetter_6);
    window.draw(thirdLetter_7);

    window.display();

    sf::sleep(sf::seconds(5));
}