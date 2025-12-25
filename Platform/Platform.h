#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Platform
{
    public:
        Platform(float x, float y, float width, float height);
        sf::RectangleShape shape;
        static void createPlatforms(std::vector<Platform>& platforms);
    };