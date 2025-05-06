#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "body_segment.h"


std::function<void(Part*)> segment_illustrate(sf::RenderWindow& window);