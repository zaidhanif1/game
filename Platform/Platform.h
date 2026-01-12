#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @class Platform
 * @brief Represents a platform or ground object in the game world
 * 
 * This class creates rectangular platforms that can be used as ground or
 * elevated surfaces for the player to stand on. Platforms are rendered
 * using SFML's RectangleShape.
 * 
 * @example
 * @code
 * Platform ground(0, 550, 800, 50, sf::Color::Green);
 * std::vector<Platform> platforms;
 * Platform::createPlatforms(platforms);
 * @endcode
 */
class Platform
{
public:
    /**
     * @brief Constructs a platform with specified position, size, and color
     * 
     * @param x      X position of the platform's top-left corner
     * @param y      Y position of the platform's top-left corner
     * @param width  Width of the platform in pixels
     * @param height Height of the platform in pixels
     * @param color  Fill color of the platform
     */
    Platform(float x, float y, float width, float height, sf::Color color);
    
    /** @brief The rectangle shape used for rendering and collision detection */
    sf::RectangleShape shape;
    
    /**
     * @brief Creates a predefined set of platforms
     * 
     * Adds a ground platform and several elevated platforms to the provided vector.
     * This is a convenience function for setting up a basic level layout.
     * 
     * @param platforms Vector to populate with platform objects
     * 
     * @note The platforms are created at fixed positions. Modify this function
     *       or create platforms manually for custom level layouts.
     */
    static void createPlatforms(std::vector<Platform>& platforms);
};