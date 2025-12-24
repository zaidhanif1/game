#include "Player.h"
#include <iostream>

Player::Player(float x, float y) 
    : sprite(texture),  // Initialize sprite with texture reference (will be empty until loadFromFile)
      velocity(0.f, 0.f),
      onGround(false),
      frameSize(36, 36),
      frameCount(4),
      currentFrame(0),
      animationSpeed(10.0f),
      frameTime(0.0f)
{
    // Set initial position
    sprite.setPosition(sf::Vector2f(x, y));
}

bool Player::loadFromFile(const std::string& filePath, 
                          const sf::Vector2u& frameSize,
                          unsigned int frameCount,
                          float animationSpeed)
{
    // Load the texture
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load texture from file: " << filePath << std::endl;
        return false;
    }
    
    // Store animation properties
    this->frameSize = frameSize;
    this->frameCount = frameCount;
    this->animationSpeed = animationSpeed;
    this->currentFrame = 0;
    this->frameTime = 0.0f;
    
    // SFML 3.0.2: Recreate sprite with the loaded texture
    // We need to preserve the position
    sf::Vector2f currentPos = sprite.getPosition();
    sprite = sf::Sprite(texture);
    sprite.setPosition(currentPos);
    
    // Set the initial texture rect to show the first frame
    sf::IntRect rect;
    rect.position = sf::Vector2i(0, 0); // top left corner of the spritesheet
    rect.size = sf::Vector2i(static_cast<int>(frameSize.x), static_cast<int>(frameSize.y)); // size of one frame
    sprite.setTextureRect(rect); //show that frame
    
    return true;
}

void Player::update(float deltaTime) 
{
    // Apply gravity
    if (!onGround) {
        velocity.y += 980.0f * deltaTime; // Gravity acceleration
    }
    
    // Update position
    sprite.move(sf::Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));
    
    // Update animation
    if (frameCount > 1) { // Only animate if multiple frames exist
        frameTime += deltaTime; // accumulate how much time has passed
        float timePerFrame = 0.5f / animationSpeed; // time per frame based on animation speed
        
        if (frameTime >= timePerFrame) { //is it time to switch frames?
            frameTime -= timePerFrame; //reset frame time but keep overflow
            currentFrame = (currentFrame + 1) % frameCount; // advance to next frame
            
            // Calculate texture rect for current frame
            // Assuming horizontal spritesheet layout
            unsigned int framesPerRow = texture.getSize().x / frameSize.x;
            unsigned int row = currentFrame / framesPerRow;
            unsigned int col = currentFrame % framesPerRow;
            
            sf::IntRect rect;
            rect.position = sf::Vector2i(
                static_cast<int>(col * frameSize.x), 
                static_cast<int>(row * frameSize.y)
            );
            rect.size = sf::Vector2i(
                static_cast<int>(frameSize.x), 
                static_cast<int>(frameSize.y)
            );
            sprite.setTextureRect(rect);
        }
    }
    
    // Reset ground flag (will be set by collision check)
    onGround = false;
}

void Player::jump() 
{
    if (onGround) {
        velocity.y = -400.0f; // Jump velocity
        onGround = false;
    }
}

sf::FloatRect Player::getGlobalBounds() const 
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const 
{
    return sprite.getPosition();
}

void Player::setPosition(const sf::Vector2f& pos) 
{
    sprite.setPosition(pos);
}
