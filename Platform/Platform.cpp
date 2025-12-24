#include <SFML/Graphics.hpp>
#include <iostream>
#include <Platform.h>

    
    Platform::Platform(float x, float y, float width, float height) 
    {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(sf::Vector2f(x, y));
        shape.setFillColor(sf::Color::Green);
    }