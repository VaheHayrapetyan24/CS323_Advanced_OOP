#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "body_segment.h"


std::function<void(Body_segment*)> segment_illustrate(sf::RenderWindow& window);