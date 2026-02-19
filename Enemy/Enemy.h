#include  "../Animation/Animation.h"
#include <SFML/Graphics.hpp>

enum class EnemyType
{
    DRAGON,
    DEMON,
    MEDUSA
};
enum class EnemyState
{
    IDLE,
    ATTACKING,
    DEAD
};

struct Dragon
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    Animation idle;
    Animation walk;
    Animation attack;
    Animation death;
    sf::Vector2u frameSize;
    Animation* current;
    EnemyState state;
    bool onGround;
    
};



class Enemy
{
    public:
        Enemy(float x, float y, EnemyType type);
        EnemyType type;
        EnemyState state;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2u frameSize;
        Animation idleAnimation;
        Animation attackingAnimation;
        Animation deadAnimation;

        struct Dragon dragon;
        bool loadDragon(struct Dragon& d);
        int frameSizeX = 96;
        int frameSizeY = 70;
        const std::string &basePath = "assets/Enemies/";
        bool loadAnimation(EnemyType type);
        void update(float deltaTime, EnemyType type);
        const sf::Sprite& getSprite(EnemyType type);
        const float GRAVITY = 980.0f;
        
};