#pragma once
#include <SFML/Graphics.hpp>


class Platform
{
    public:
        Platform(float x, float y, float width, float height);
        sf::RectangleShape shape;
};