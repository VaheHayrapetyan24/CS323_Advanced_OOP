// #include <SFML/Graphics.hpp>

#include "segment.h"
#include "point.h"
#include "line.h"

int main()
{
    // sf::RenderWindow window(sf::VideoMode(400, 400), "Line Example");

    // // Define two points
    // sf::Vertex line[] =
    // {
    //     sf::Vertex(sf::Vector2f(50.f, 50.f), sf::Color::Red),
    //     sf::Vertex(sf::Vector2f(350.f, 350.f), sf::Color::Red)
    // };

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
    //     window.draw(line, 2, sf::Lines);
    //     window.display();
    // }

    Point p1(0.f, 0.f), p2(1.f,1.f);
    Line l(p1, p2);
    Body_segment bs(l);

    return 0;
}
