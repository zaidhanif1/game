#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include "../Platform/Platform.h"
#include <optional>


class Collision 
{
public:
    std::optional<sf::FloatRect> getIntersection(const Player& player, const Platform& platform);
    void handleCollision(Player& player, const Platform& platform);
};