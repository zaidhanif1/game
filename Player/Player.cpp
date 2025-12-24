#include <SFML/Graphics.hpp>
#include <Player/Player.h>
#include <iostream>


    
    Player::Player(float x, float y) {
        velocity = sf::Vector2f(0, 0);
        onGround = false;
    }

    void Player::update(float deltaTime) {
        // Apply gravity
        if (!onGround) {
            velocity.y += 980.0f * deltaTime; // Gravity acceleration
        }
        
        // Update position
        shape.move(sf::Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));
        
        // Reset ground flag (will be set by collision check)
        onGround = false;
    }

    void Player::jump() {
        if (onGround) {
            velocity.y = -400.0f; // Jump velocity
            onGround = false;
        }
    }
    void Player::loadFromFile(const std::string& filename) 
    {
        if (!texture.loadFromFile(filename)) {
            std::cerr << "Failed to load texture from file: " << filename << std::endl;
            return;
        }
        shape.setTexture(&texture, true);
    }

    void Player::setSprite() 
    {
        sprite.setTexture(texture);
    }
