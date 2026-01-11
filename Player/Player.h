#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Animation/Animation.h"

enum class PlayerState 
{
    IDLE,
    WALK,
    RUN,
    JUMP,
};

class Player 
{
public:

// Constructor - takes initial position
    Player(float x, float y);

    // Animation states
    Animation idleAnimation;
    Animation walkAnimation;
    Animation runAnimation;
    Animation jumpAnimation;
    Animation* currentAnimation;  // Pointer to currently playing animation
    PlayerState currentState; // enum storing current state


    bool facingRight;  // true = facing right, false = facing left
    bool onGround;  // true = on ground, false = in air

    sf::Vector2f velocity;
    sf::Vector2u frameSize;
    int frameSizeX = 96; //96 pixels wide
    int frameSizeY = 70; //70 pixels tall (sprite sheet specific)

    const float WALK_SPEED = 200.0f;
    const float RUN_SPEED = 350.0f;
    const float GRAVITY = 980.0f; // pixels per second squared
    
    // Load all animations (call once at initialization)
    bool loadAnimations(const std::string& basePath = "assets/with_outline/");
    
    // Load individual animation (for custom paths)
    bool loadAnimation(Animation& anim, const std::string& filePath, 
                       const sf::Vector2u& frameSize, 
                       unsigned int frameCount, 
                       float fps);
    
    void update(float deltaTime);
    void jump();
    
    // Get bounds for collision detection
    sf::FloatRect getGlobalBounds() const;
    
    // Position helpers
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    
    // Get sprite for rendering (returns current animation's sprite)
    const sf::Sprite& getSprite() const;
    
    // Update animation state (call after collision detection for accurate onGround)
    void updateAnimationState();
    
    // Update current animation (call AFTER updateAnimationState to avoid flashing)
    void updateAnimation(float deltaTime);
    
private:
    // Switch to a specific animation state
    void setAnimation(PlayerState newState);
};
