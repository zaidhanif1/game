#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "../GameObject/GameObject.h"


class Dragon : public Enemy
{
    public:
        Dragon(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f frame_size, sf::Vector2f hit_box_dimensions);

};
