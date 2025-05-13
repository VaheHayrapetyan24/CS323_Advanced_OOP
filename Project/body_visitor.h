#pragma once
#include <SFML/Graphics.hpp>

class Body_segment;
class Head;
class Body;

class Body_visitor {
    public:
        virtual void visit(class Body_segment* body_segment) = 0;
        virtual void visit(class Head* head) = 0;
        virtual void visit(class Body* body) = 0;
};


class Body_drawer: public Body_visitor {
    public:
        Body_drawer(sf::RenderWindow& window): window(window) {}
        void visit(Body_segment* body_segment) override;
        void visit(Head* head) override;
        void visit(Body* body) override;
    private:
        sf::RenderWindow& window;
};