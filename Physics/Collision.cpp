#include <optional>
#include "Collision.h"


std::optional<sf::FloatRect> Collision::getIntersection(const GameObject& entity, const Platform& platform) 
{
    sf::FloatRect entityBounds = entity.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    return entityBounds.findIntersection(platformBounds);
}

void Collision::handleCollision(GameObject& entity, const Platform& platform) 
{
    std::optional<sf::FloatRect> intersection = getIntersection(entity, platform);
    
    if (!intersection.has_value()) 
    {
        return;
    }
    
    sf::FloatRect overlap = intersection.value();

    sf::Vector2f entityPos = entity.getPosition();
    sf::FloatRect entityBounds = entity.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    if (overlap.size.x < overlap.size.y) 
    {
        // Horizontal collision (left/right)
        if (entityBounds.position.x < platformBounds.position.x) 
        {
            entity.setPosition(
                sf::Vector2f(entityPos.x - overlap.size.x, entityPos.y)
            );
        } 
        else 
        {
            entity.setPosition(
                sf::Vector2f(entityPos.x + overlap.size.x, entityPos.y)
            );
        }
        entity.velocity.x = 0;
    } 
    else 
    {
        // Vertical collision (top/bottom)
        if (entityBounds.position.y < platformBounds.position.y) 
        {
            // Landed on top — tiny overlap prevents onGround flicker
            entity.setPosition(
                sf::Vector2f(entityPos.x, entityPos.y - overlap.size.y + 0.1f)
            );
            entity.velocity.y = 0;
            entity.onGround = true;
        } 
        else 
        {
            // Hit from below
            entity.setPosition(
                sf::Vector2f(entityPos.x, entityPos.y + overlap.size.y)
            );
            entity.velocity.y = 0;
        }
    }
}