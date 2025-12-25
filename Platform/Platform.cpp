#include "Platform.h"
#include <SFML/Graphics.hpp>
#include <iostream>

    
    Platform::Platform(float x, float y, float width, float height) 
    {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(sf::Vector2f(x, y));
        shape.setFillColor(sf::Color::Green);
    }

    void Platform::createPlatforms(std::vector<Platform> &platforms)
    {
        
    }
