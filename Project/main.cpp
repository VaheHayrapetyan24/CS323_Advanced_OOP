#include <SFML/Graphics.hpp>

#include "body_segment.h"
#include "point.h"
#include "line.h"

#include "segment_illustrate.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Line Example");

    Point p1(50.f, 50.f), p2(350.f,350.f);
    Line l(p1, p2);
    Point p3(50.f, 350.f), p4(350.f, 50.f);
    Line l2(p2, p3);
    std::vector<Part*> subsegments;
    Body_segment bs2(l2);
    subsegments.push_back(&bs2);

    Body_segment bs(l, &subsegments);
    auto fn = segment_illustrate(window);

    int i = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        fn(&bs);

        // if (i % 10 == 0) {
            // bs.shift(1, 1);
            bs.rotate_around(p1.get_x(), p1.get_y(), 0.1f);
        // }

        window.display();
    }

    

    return 0;
}
