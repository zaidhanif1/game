#include <optional>
#include "Collision.h"
#include <iostream>
// Check collision and get intersection using findIntersection
std::optional<sf::FloatRect> Collision::getIntersection(const Player& player, const Platform& platform) 
{
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    return playerBounds.findIntersection(platformBounds);
}

// Handle player-platform collision using intersection data
void Collision::handleCollision(Player& player, const Platform& platform) 
{
    std::optional<sf::FloatRect> intersection = getIntersection(player, platform);
    
    if (!intersection.has_value()) 
    {
        return; // No collision
    }
    
    // Print the intersection values
    sf::FloatRect overlap = intersection.value();
   

    sf::Vector2f playerPos = player.getPosition();
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    // Determine collision direction based on intersection size
    // If overlap is wider than it is tall, it's a vertical collision
    // If overlap is taller than it is wide, it's a horizontal collision
    
    if (overlap.size.x < overlap.size.y) 
    {
        // Horizontal collision (left/right)
        if (playerBounds.position.x < platformBounds.position.x) 
        {
            // Player hit from the left - push player left
            player.setPosition(sf::Vector2f(
                playerPos.x - overlap.size.x,
                playerPos.y
            ));
        } 
        else 
        {
            // Player hit from the right - push player right
            player.setPosition(sf::Vector2f(
                playerPos.x + overlap.size.x,
                playerPos.y
            ));
        }
        player.velocity.x = 0;
    } 
    else 
    {
        // Vertical collision (top/bottom)
        if (playerBounds.position.y < platformBounds.position.y) 
        {
            // Player landed on top of platform
            // Leave a tiny overlap (0.1 pixels) so collision continues to detect ground next frame
            // This prevents onGround from flickering between true/false
            player.setPosition(sf::Vector2f(
                playerPos.x,
                playerPos.y - overlap.size.y + 0.1f
            ));
            player.velocity.y = 0;
            player.onGround = true;
        } 
        else 
        {
            // Player hit platform from below
            player.setPosition(sf::Vector2f(
                playerPos.x,
                playerPos.y + overlap.size.y
            ));
            player.velocity.y = 0;
        }
    }
}

