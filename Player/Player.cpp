#include "Player.h"
#include <iostream>

Player::Player(float x, float y) 
    : velocity(0.f, 0.f),
      onGround(false)
{
    animation.setPosition(sf::Vector2f(x, y));
}

bool Player::loadFromFile(const std::string& filePath, 
                          const sf::Vector2u& frameSize,
                          unsigned int frameCount,
                          float animationSpeed)
{
    return animation.loadFromFile(filePath, frameSize, frameCount, animationSpeed);
}

void Player::update(float deltaTime) 
{
    // Apply gravity
    if (!onGround) {
        velocity.y += 980.0f * deltaTime;
    }
    
    // Update position
    sf::Vector2f pos = animation.getPosition();
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
    animation.setPosition(pos);
    
    // Update animation
    animation.update(deltaTime);
    
    onGround = false;
}

void Player::jump() 
{
    if (onGround) {
        velocity.y = -400.0f;
        onGround = false;
    }
}

sf::FloatRect Player::getGlobalBounds() const 
{
    return animation.getSprite().getGlobalBounds();
}

sf::Vector2f Player::getPosition() const 
{
    return animation.getPosition();
}

void Player::setPosition(const sf::Vector2f& pos) 
{
    animation.setPosition(pos);
}