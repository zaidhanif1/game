#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include "Player/Player.h"
#include "Platform/Platform.h"
#include "Physics/Collision.h"
#include <iostream>



int main()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Game");
    window.setFramerateLimit(75);
    // Create player
    Player player(20, 550);
    // Load all animations once at startup
    if (!player.loadAnimations()) 
    {
        std::cerr << "Failed to load player animations!" << std::endl;
        return -1;
    }
    // Create platforms
    std::vector<Platform> platforms;
    Platform::createPlatforms(platforms);
    
    // Collision handler from physics/
    Collision collisionHandler;

    // Clock for delta time
    sf::Clock clock;
    
    // Enter game loop
    while ( window.isOpen() )
    {
        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();
        
        // Handle close event
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        // Handle user input
        
        player.velocity.x = 0; // Reset horizontal velocity
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) 
            {
            player.velocity.x = -player.RUN_SPEED; 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) 
        {
            player.velocity.x = player.RUN_SPEED;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) 
        {
            player.jump();
        }
        
        // Update player (position, velocity, etc.)
        player.update(deltaTime);
        
        // Check collisions with all platforms
        for (auto& platform : platforms) 
        {
            collisionHandler.handleCollision(player, platform);
        }
        
        // Update animation state AFTER collision detection
        // This ensures onGround is correctly set before determining animation
        player.updateAnimationState();
        
        // Update the animation AFTER state is determined to avoid flashing
        player.updateAnimation(deltaTime);
        
        // Keep player in bounds (optional)
        sf::FloatRect bounds = player.getGlobalBounds();
        if (player.getPosition().x < 0) 
        {
            player.setPosition(sf::Vector2f(0, player.getPosition().y));
        }
        if (player.getPosition().x + bounds.size.x > 800) 
        {
            player.setPosition(sf::Vector2f(800 - bounds.size.x, player.getPosition().y));
        }
        
        // Clear screen
        window.clear(sf::Color(135, 206, 235)); // Random blue sky blue background (need to change to var later)
         
        // Draw platforms
        for (auto& platform : platforms) 
        {
            window.draw(platform.shape);
        }
        
        // Draw player (automatically uses correct animation based on state)
        window.draw(player.getSprite());
        
        // display everything
        window.display();
    }
    
    return 0;
}