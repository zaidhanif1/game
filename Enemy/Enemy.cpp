#include "Enemy.h"
#include "../Player/Player.h"

Enemy::Enemy(float x, float y, EnemyType type)
    : 
    position(x, y),
    velocity(0.f, 0.f)
{

}
bool Enemy::loadDragon(struct Dragon& d)
{
    bool success = true;
    d.frameSize.x = 256;
    d.frameSize.y = 256;
    d.position.x = 0.f;
    d.position.y = 0.f;
    d.onGround = false;


    
    success &= d.idle.loadFromFile("assets/Enemies/dragon/Idle.png", d.frameSize, 3, 8.0);
    success &= d.walk.loadFromFile("assets/Enemies/dragon/Walk.png", d.frameSize, 5, 8.0);
    success &= d.attack.loadFromFile("assets/Enemies/dragon/Attack.png", d.frameSize, 4, 8.0);
    success &= d.death.loadFromFile("assets/Enemies/dragon/Death.png", d.frameSize, 5, 8.0);
    
    d.current = &d.idle;
    d.state = EnemyState::IDLE;

    d.idle.play();
    return success;
}


bool Enemy::loadAnimation(EnemyType type)
{
    switch(type)
    {
        case EnemyType::DRAGON:
            if (!loadDragon(dragon))
            {
                return false;
            }
            return true;
    }
    return true;
}

void Enemy::update(float deltaTime, EnemyType type)
{
    switch (type)
    {
        case EnemyType::DRAGON:
            if (!dragon.onGround)
            {
                dragon.velocity.y += GRAVITY * deltaTime;

            }
            dragon.position.x += dragon.velocity.x * deltaTime;
            dragon.position.y += dragon.velocity.y * deltaTime;
            dragon.current->setPosition(position);
            dragon.current->update(deltaTime);
            break;
        default:
            break;
    }
}

const sf::Sprite &Enemy::getSprite(EnemyType type) {
    
    switch(type)
    {
        case EnemyType::DRAGON:
        {
            return this->dragon.current->getSprite();
        }
    }
    
};
