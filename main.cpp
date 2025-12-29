#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include "Player/Player.h"
#include "Platform/Platform.h"


// Check collision between player and platform
bool checkCollision(const Player& player, const Platform& platform) {
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    // Manual AABB collision detection
    return (playerBounds.position.x < platformBounds.position.x + platformBounds.size.x &&
            playerBounds.position.x + playerBounds.size.x > platformBounds.position.x &&
            playerBounds.position.y < platformBounds.position.y + platformBounds.size.y &&
            playerBounds.position.y + playerBounds.size.y > platformBounds.position.y);
}

// Handle player-platform collision
void handleCollision(Player& player, const Platform& platform) {
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    float playerTop = playerBounds.position.y;
    float playerLeft = playerBounds.position.x;
    float playerHeight = playerBounds.size.y;
    float playerWidth = playerBounds.size.x;
    
    float platformTop = platformBounds.position.y;
    float platformLeft = platformBounds.position.x;
    float platformHeight = platformBounds.size.y;
    float platformWidth = platformBounds.size.x;
    
    // Check if player is above platform (landing on top)
    if (playerTop + playerHeight <= platformTop + 10 && 
        player.velocity.y > 0) {
        player.setPosition(sf::Vector2f(playerLeft, platformTop - playerHeight));
        player.velocity.y = 0;
        player.onGround = true;
    }
    // Check if player hits platform from below
    else if (playerTop >= platformTop + platformHeight - 10 && 
             player.velocity.y < 0) {
        player.setPosition(sf::Vector2f(playerLeft, platformTop + platformHeight));
        player.velocity.y = 0;
    }
    // Check side collisions
    else if (playerLeft < platformLeft + platformWidth / 2) {
        // Hit from left
        player.setPosition(sf::Vector2f(platformLeft - playerWidth, playerTop));
        player.velocity.x = 0;
    }
    else {
        // Hit from right
        player.setPosition(sf::Vector2f(platformLeft + platformWidth, playerTop));
        player.velocity.x = 0;
    }
}

int main()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "2D Platformer - SFML");
    window.setFramerateLimit(60);
    
    // Create player
    Player player(100, 100);
    // Load the spritesheet - adjust frameSize and frameCount based on your spritesheet
    player.animation.loadFromFile("images/transparent.png", 
                        sf::Vector2u(36, 36),  // Frame size (width, height)
                        6,                      // Number of frames for idle animation
                        8.0f);                  // Animation speed (frames per second)
    
    
    // Create platforms
    std::vector<Platform> platforms;
    platforms.push_back(Platform(0, 550, 800, 50));      // Ground
    platforms.push_back(Platform(200, 450, 150, 20));    // Platform 1
    platforms.push_back(Platform(400, 350, 150, 20));    // Platform 2
    platforms.push_back(Platform(600, 250, 150, 20));    // Platform 3

    
    // Clock for delta time
    sf::Clock clock;
    
    // Game loop
    while (window.isOpen())
    {
        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();
        
        // Handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        // Handle input
        float moveSpeed = 300.0f;
        player.velocity.x = 0; // Reset horizontal velocity
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player.velocity.x = -moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player.velocity.x = moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player.jump();
        }
        
        // Update player
        player.update(deltaTime);
        
        // Check collisions with all platforms
        for (auto& platform : platforms) {
            if (checkCollision(player, platform)) {
                handleCollision(player, platform);
            }
        }
        
        // Keep player in bounds (optional)
        sf::FloatRect bounds = player.getGlobalBounds();
        if (player.getPosition().x < 0) {
            player.setPosition(sf::Vector2f(0, player.getPosition().y));
        }
        if (player.getPosition().x + bounds.size.x > 800) {
            player.setPosition(sf::Vector2f(800 - bounds.size.x, player.getPosition().y));
        }
        
        // Clear screen
        window.clear(sf::Color(135, 206, 235)); // Sky blue background
        
        // Draw platforms
        for (auto& platform : platforms) {
            window.draw(platform.shape);
        }
        
        // Draw player
        window.draw(player.animation.getSprite());
        
        // Display everything
        window.display();
    }
    
    return 0;
}
