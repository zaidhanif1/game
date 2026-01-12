#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include "../Platform/Platform.h"
#include <optional>

/**
 * @class Collision
 * @brief Handles collision detection and resolution between Player and Platform objects
 * 
 * This class provides utilities for detecting intersections between player and platform
 * objects, and resolving collisions by adjusting the player's position and velocity.
 * 
 * @note Collision resolution uses overlap size to determine collision direction:
 *       - Horizontal collisions occur when overlap width < overlap height
 *       - Vertical collisions occur when overlap width >= overlap height
 * 
 * @example
 * @code
 * Collision collision;
 * std::optional<sf::FloatRect> intersection = collision.getIntersection(player, platform);
 * if (intersection.has_value()) {
 *     collision.handleCollision(player, platform);
 * }
 * @endcode
 */
class Collision 
{
public:
    /**
     * @brief Checks for intersection between a player and platform
     * 
     * Calculates the intersection rectangle between the player's bounds and
     * the platform's bounds. Returns an empty optional if no collision exists.
     * 
     * @param player   The player object to check collision for
     * @param platform The platform object to check collision against
     * @return Optional containing the intersection rectangle if collision exists,
     *         empty optional otherwise
     */
    std::optional<sf::FloatRect> getIntersection(const Player& player, const Platform& platform);
    
    /**
     * @brief Resolves collision between player and platform
     * 
     * Adjusts the player's position to resolve the collision based on the
     * collision direction. Also updates player velocity and onGround state.
     * 
     * @param player   The player object to adjust (non-const, will be modified)
     * @param platform The platform involved in the collision
     * 
     * @note For top collisions, a small overlap (0.1 pixels) is maintained to
     *       prevent flickering of the onGround flag between frames
     */
    void handleCollision(Player& player, const Platform& platform);
};