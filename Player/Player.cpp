#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(float x, float y) 
    : velocity(0.f, 0.f),
      onGround(false),
      currentState(PlayerState::IDLE),
      facingRight(true),
      currentAnimation(nullptr)
{
    // set initial position for all animations
    idleAnimation.setPosition(sf::Vector2f(x, y));
    walkAnimation.setPosition(sf::Vector2f(x, y));
    runAnimation.setPosition(sf::Vector2f(x, y));
    jumpAnimation.setPosition(sf::Vector2f(x, y));
}

bool Player::loadAnimations(const std::string& basePath)
{
    bool success = true;
    frameSize.x = frameSizeX;
    frameSize.y = frameSizeY;
    
    // get the initial position (set in constructor)
    sf::Vector2f initialPos = idleAnimation.getPosition();
    
    // load all animations
    success &= loadAnimation(idleAnimation, basePath + "IDLE.png", frameSize, 6, 8.0f);
    success &= loadAnimation(walkAnimation, basePath + "WALK.png", frameSize, 6, 12.0f);
    success &= loadAnimation(runAnimation, basePath + "RUN.png", frameSize, 6, 15.0f);
    success &= loadAnimation(jumpAnimation, basePath + "JUMP.png", frameSize, 5, 10.0f);
    
    idleAnimation.setLoop(true);
    walkAnimation.setLoop(true);
    runAnimation.setLoop(true);
    jumpAnimation.setLoop(true);


    // set initial animation
    currentAnimation = &idleAnimation;
    currentState = PlayerState::IDLE;
    
    // start the idle animation
    idleAnimation.play();
    
    return success;
}

bool Player::loadAnimation(Animation& animation, const std::string& filePath, 
                           const sf::Vector2u& frameSize, 
                           unsigned int frameCount, 
                           float fps)
{
    // get current position before loading (if animation was already positioned)
    sf::Vector2f oldPos = animation.getPosition();
    if (!animation.loadFromFile(filePath, frameSize, frameCount, fps)) 
    {
        return false;
    }
    // set origin to center of frame for proper flipping
    animation.setOrigin(sf::Vector2f(frameSize.x / 2.0f, frameSize.y / 2.0f));
    // adjust position: if old position was top-left, new position (center) should be offset
    animation.setPosition(sf::Vector2f(oldPos.x + frameSize.x / 2.0f, oldPos.y + frameSize.y / 2.0f));
    
    return true;
}

void Player::update(float deltaTime) 
{
    // apply gravity
    if (!onGround) 
    {
        velocity.y += GRAVITY * deltaTime;
    }
    
    // get current position (center point, since origin is at center)
    sf::Vector2f pos = currentAnimation ? currentAnimation->getPosition() : sf::Vector2f(0, 0);
    
    // update position based on velocity
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
    
    // handle sprite flipping based on direction (apply to ALL animations for consistency)
    bool newFacingRight = facingRight;
    if (velocity.x > 0.1f) 
    {
        newFacingRight = true;
    } 
    else if (velocity.x < -0.1f) 
    {
        newFacingRight = false;
    }
    
    // only update scale if direction changed (to avoid constant updates)
    if (newFacingRight != facingRight) 
    {
        facingRight = newFacingRight;
        sf::Vector2f scale = facingRight ? sf::Vector2f(1.0f, 1.0f) : sf::Vector2f(-1.0f, 1.0f);
        
        // apply scale to ALL animations to keep them in sync
        idleAnimation.setScale(scale);
        walkAnimation.setScale(scale);
        runAnimation.setScale(scale);
        jumpAnimation.setScale(scale);
    }
    
    // update all animation positions (after scale is set, so they all align)
    // since origin is at center, position represents the center point
    idleAnimation.setPosition(pos);
    walkAnimation.setPosition(pos);
    runAnimation.setPosition(pos);
    jumpAnimation.setPosition(pos);
    
    // reset onGround - collision system will set it to true if player is on a platform
    onGround = false;
}

void Player::updateAnimation(float deltaTime)
{
    // update the current animation - call this AFTER updateAnimationState()
    if (currentAnimation) 
    {
        currentAnimation->update(deltaTime);
    }
}

void Player::updateAnimationState()
{
    // determine which animation should be playing based on player state
    PlayerState newState = currentState;
    
    // priority order: JUMP > RUN > WALK > IDLE
    if (!onGround) 
    {
        newState = PlayerState::JUMP;
    } 
    else if (std::abs(velocity.x) > 250.0f) 
    {  // run threshold (moveSpeed is 300, so this catches running)
        newState = PlayerState::RUN;
    } 
    else if (std::abs(velocity.x) > 10.0f) 
    {  // walk threshold 
        newState = PlayerState::WALK;
    } 
    else 
    {
        newState = PlayerState::IDLE;
    }
    
    // only switch if state actually changed
    if (newState != currentState) {
        setAnimation(newState);
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
    if (currentAnimation) 
    {
        return currentAnimation->getSprite().getGlobalBounds();
    }
    return sf::FloatRect();
}

sf::Vector2f Player::getPosition() const 
{
    if (currentAnimation) 
    {
        return currentAnimation->getPosition();
    }
    return sf::Vector2f(0, 0);
}

void Player::setPosition(const sf::Vector2f& pos) 
{
    idleAnimation.setPosition(pos);
    walkAnimation.setPosition(pos);
    runAnimation.setPosition(pos);
    jumpAnimation.setPosition(pos);
}

const sf::Sprite& Player::getSprite() const
{
    if (currentAnimation) 
    {
        return currentAnimation->getSprite();
    }
    // fallback to idle if somehow currentAnimation is null
    return idleAnimation.getSprite();
}