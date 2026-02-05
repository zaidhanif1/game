#include  "../Animation/Animation.h"
#include <SFML/Graphics.hpp>

enum class EnemyType
{
    ZOMBIE,
    ALIEN,
    ROBOT
};

enum class EnemyState
{
    IDLE,
    ATTACKING,
    DEAD
};


class Enemy
{
    public:
        Enemy(float x, float y);
        EnemyType type;
        EnemyState state;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2u frameSize;
        Animation idleAnimation;
        Animation attackingAnimation;
        Animation deadAnimation;

        int frameSizeX = 96;
        int frameSizeY = 70;
        
};