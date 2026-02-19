#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(float x, float y) 
    : 
    position(x, y),
    velocity(0.f, 0.f),
    onGround(false),
    currentState(PlayerState::IDLE),
    facingRight(true),
    currentAnimation(nullptr)
{
}
bool Player::loadAllAnimations(const std::string& basePath)
{
    bool success = true;
    this->frameSize.x = frameSizeX;
    this->frameSize.y = frameSizeY;
    
    // Load all animations
    success &= loadAnimation(idleAnimation, basePath + "IDLE.png", this->frameSize, 6, 8.0f);
    success &= loadAnimation(walkAnimation, basePath + "WALK.png", this->frameSize, 6, 12.0f);
    success &= loadAnimation(runAnimation, basePath + "RUN.png", this->frameSize, 6, 15.0f);
    success &= loadAnimation(jumpAnimation, basePath + "JUMP.png", this->frameSize, 5, 10.0f);
    
    
    

    // Set initial animation
    currentAnimation = &idleAnimation;
    currentState = PlayerState::IDLE;
    
    // Start the idle animation
    idleAnimation.play();
    
    return success;
}

bool Player::loadAnimation(Animation& animation, const std::string& filePath, 
                           const sf::Vector2u& frameSize, 
                           unsigned int frameCount, 
                           float fps)
{
    if (!animation.loadFromFile(filePath, frameSize, frameCount, fps)) 
    {
        return false;
    }
    // Set origin to center of frame for proper flipping
    animation.setOrigin(sf::Vector2f(frameSize.x / 2.0f, frameSize.y / 2.0f));
    // Position animation at the player's current position
    animation.setPosition(position);
    
    return true;
}

void Player::update(float deltaTime) 
{
    // Apply gravity
    if (!onGround) 
    {
        velocity.y += GRAVITY * deltaTime;
    }
    
    // Update position based on velocity (position is the source of truth)
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    
    // Handle sprite flipping based on direction (apply to ALL animations for consistency)
    bool newFacingRight = facingRight;
    if (velocity.x > 0.1f) 
    {
        newFacingRight = true;
    } 
    else if (velocity.x < -0.1f) 
    {
        newFacingRight = false;
    }
    
    // Only update scale if direction changed (to avoid constant updates)
    if (newFacingRight != facingRight) 
    {
        facingRight = newFacingRight;
        sf::Vector2f scale = facingRight ? sf::Vector2f(1.0f, 1.0f) : sf::Vector2f(-1.0f, 1.0f);
        
        // Apply scale to ALL animations to keep them in sync
        idleAnimation.setScale(scale);
        walkAnimation.setScale(scale);
        runAnimation.setScale(scale);
        jumpAnimation.setScale(scale);
    }
    
    // Sync all animation positions with player's position
    idleAnimation.setPosition(position);
    walkAnimation.setPosition(position);
    runAnimation.setPosition(position);
    jumpAnimation.setPosition(position);
    
    // Reset onGround - collision system will set it to true if player is on a platform
    onGround = false;
}


void Player::updateAnimationState()
{
    // Determine which animation should be playing based on player state
    PlayerState newState = currentState;
    
    // Priority order: JUMP > RUN > WALK > IDLE
    if (!onGround) 
    {
        newState = PlayerState::JUMP;
    } 
    else if (std::abs(velocity.x) > 250.0f) 
    {  // Run threshold (moveSpeed is 300, so this catches running)
        newState = PlayerState::RUN;
    } 
    else if (std::abs(velocity.x) > 10.0f) 
    {  // Walk threshold 
        newState = PlayerState::WALK;
    } 
    else 
    {
        newState = PlayerState::IDLE;
    }
    
    // Only switch if state actually changed
    if (newState != currentState) 
    {
        setAnimation(newState);
    }
}

void Player::updateAnimation(float deltaTime)
{
    // Update the current animation - call this AFTER updateAnimationState()
    if (currentAnimation) 
    {
        currentAnimation->update(deltaTime);
    }
}

void Player::setAnimation(PlayerState newState)
{
    // don't do anything if already in this state
    if (newState == currentState) 
    {
        return;
    }
    
    currentState = newState;
    
    // switch to new animation
    switch (newState) 
    {
        case PlayerState::IDLE:
            currentAnimation = &idleAnimation;
            break;
        case PlayerState::WALK:
            currentAnimation = &walkAnimation;
            break;
        case PlayerState::RUN:
            currentAnimation = &runAnimation;
            break;
        case PlayerState::JUMP:
            currentAnimation = &jumpAnimation;
            break;
    }
    
    // reset the animation to start fresh - this prevents showing invalid/blank frames
    // when switching between animations with different frame counts
    if (currentAnimation) 
    {
        currentAnimation->currentFrame = 0;
        currentAnimation->frameTime = 0.0f;
        currentAnimation->updateTextureRect();
        currentAnimation->play();
    }
}

void Player::jump() 
{
    if (onGround) 
    {
        velocity.y = -470.0f;
        onGround = false;
    }
}

sf::FloatRect Player::getGlobalBounds() const 
{
    // Calculate custom collision box centered on the player's position
    // The box is offset from center: top-left corner is at (center.x - width/2, center.y - height/2)
    // We offset the Y slightly toward the bottom since feet should be the reference point
    return sf::FloatRect
    (
        sf::Vector2f(position.x - (hitboxSizeX / 2.0f), position.y - (hitboxSizeY / 2.0f) + 5.0f),
        sf::Vector2f(static_cast<float>(hitboxSizeX), static_cast<float>(hitboxSizeY))
    );
}

sf::Vector2f Player::getPosition() const 
{
    return position;
}

void Player::setPosition(const sf::Vector2f& pos) 
{
    position = pos;
    // Sync all animation positions
    idleAnimation.setPosition(position);
    walkAnimation.setPosition(position);
    runAnimation.setPosition(position);
    jumpAnimation.setPosition(position);
}

const sf::Sprite& Player::getSprite()
{
    if (currentAnimation) 
    {
        return currentAnimation->getSprite();
    }
    // fallback to idle if somehow currentAnimation is null
    return idleAnimation.getSprite();
}