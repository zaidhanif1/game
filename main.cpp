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
    // create window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Game");
    window.setFramerateLimit(75);
    // create player
    Player player(20, 550);
    // load all animations once at startup
    if (!player.loadAnimations()) 
    {
        std::cerr << "Failed to load player animations!" << std::endl;
        return -1;
    }
    // create platforms
    std::vector<Platform> platforms;
    Platform::createPlatforms(platforms);
    
    // collision handler from physics/
    Collision collisionHandler;

    // clock for delta time
    sf::Clock clock;
    
    // enter game loop
    while ( window.isOpen() )
    {
        // calculate delta time
        float deltaTime = clock.restart().asSeconds();
        
        // handle close event
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        // handle user input
        
        player.velocity.x = 0; // reset horizontal velocity
        
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
        
        // update player (position, velocity, etc.)
        player.update(deltaTime);
        
        // check collisions with all platforms
        for (auto& platform : platforms) 
        {
            collisionHandler.handleCollision(player, platform);
        }
        
        // update animation state AFTER collision detection
        // this ensures onGround is correctly set before determining animation
        player.updateAnimationState();
        
        // update the animation AFTER state is determined to avoid flashing
        player.updateAnimation(deltaTime);
        
        // keep player in bounds (optional)
        sf::FloatRect bounds = player.getGlobalBounds();
        if (player.getPosition().x < 0) 
        {
            player.setPosition(sf::Vector2f(0, player.getPosition().y));
        }
        if (player.getPosition().x + bounds.size.x > 800) 
        {
            player.setPosition(sf::Vector2f(800 - bounds.size.x, player.getPosition().y));
        }
        
        // clear screen
        window.clear(sf::Color(135, 206, 235)); // random blue sky blue background (need to change to var later)
         
        // draw platforms
        for (auto& platform : platforms) {
            window.draw(platform.shape);
        }
        
        // draw player (automatically uses correct animation based on state)
        window.draw(player.getSprite());
        
        // display everything
        window.display();
    }
    
    return 0;
}