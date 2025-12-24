#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player 
{
public:
    // Texture must be stored (sprite references it)
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool onGround;
    
    // Animation properties
    sf::Vector2u frameSize;
    unsigned int frameCount;
    unsigned int currentFrame;
    float animationSpeed;
    float frameTime;
    
    // Constructor - takes initial position
    Player(float x, float y);
    
    // Load spritesheet and set up animation
    bool loadFromFile(const std::string& filePath, 
                      const sf::Vector2u& frameSize = sf::Vector2u(36, 36),
                      unsigned int frameCount = 4,
                      float animationSpeed = 10.0f);
    
    void update(float deltaTime);
    void jump();
    
    // Get bounds for collision detection
    sf::FloatRect getGlobalBounds() const;
    
    // Position helpers
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);
};
