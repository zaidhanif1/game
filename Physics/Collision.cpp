#include <optional>
#include "Collision.h"
#include <iostream>


// check collision and get intersection using findIntersection
std::optional<sf::FloatRect> Collision::getIntersection(const Player& player, const Platform& platform) 
{
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    return playerBounds.findIntersection(platformBounds);
}

// handle player/platform collision using intersection data
void Collision::handleCollision(Player& player, const Platform& platform) 
{
    std::optional<sf::FloatRect> intersection = getIntersection(player, platform);
    
    if (!intersection.has_value()) 
    {
        return; // no collision, return early
    }
    
    // print the intersection values
    sf::FloatRect overlap = intersection.value();
   

    sf::Vector2f playerPos = player.getPosition();
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    // determine collision direction based on intersection size
    // if overlap is wider than it is tall, it's a vertical collision (intersection rectangle is wider than tall)
    // if overlap is taller than it is wide, it's a horizontal collision (intersection rectangle is taller than wide)
    
    if (overlap.size.x < overlap.size.y) 
    {
        // horizontal collision (left/right)
        if (playerBounds.position.x < platformBounds.position.x) 
        {
            // player hit from the left - push player left
            player.setPosition(
                sf::Vector2f
                (
                    playerPos.x - overlap.size.x,
                    playerPos.y
                )
            );
        } 
        else 
        {
            // player hit from the right - push player right
            player.setPosition(
                sf::Vector2f
                (
                    playerPos.x + overlap.size.x,
                    playerPos.y
                )
            );
        }
        player.velocity.x = 0;
    } 
    else 
    {
        // vertical collision (top/bottom)
        if (playerBounds.position.y < platformBounds.position.y) 
        {
            // player landed on top of platform
            // leave a tiny overlap (0.1 pixels) so collision continues to detect ground next frame
            // this prevents onGround from flickering between true/false
            player.setPosition(
                sf::Vector2f
                (
                    playerPos.x,
                    playerPos.y - overlap.size.y + 0.1f
                )
            );
            player.velocity.y = 0;
            player.onGround = true;
        } 
        else 
        {
            // player hit platform from below
            player.setPosition(
                sf::Vector2f
                (
                    playerPos.x,
                    playerPos.y + overlap.size.y
                )
            );
            player.velocity.y = 0;
        }
    }
}