#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include "Player/Player.h"  // Assuming Player class is defined in Player.h
#include "Platform/Platform.h"  // Assuming Platform class is defined in Platform.h



class AnimatedSprite {
public:
    std::optional<sf::Sprite> sprite;
    sf::Texture texture;
    
    // Animation properties
    sf::Vector2u frameSize;      // Size of each frame (width, height)
    unsigned int frameCount;      // Total number of frames in the animation
    unsigned int currentFrame;    // Current frame index
    float animationSpeed;         // Frames per second
    float frameTime;              // Time accumulator for frame switching
    
    // Animation state
    bool isPlaying;                // Whether animation is playing
    bool loop;                     // Whether to loop the animation
    
    AnimatedSprite() : frameCount(0), currentFrame(0), animationSpeed(10.0f), 
                       frameTime(0.0f), isPlaying(true), loop(true) {
        // Sprite will be initialized when texture is loaded
    }
    
    // Load texture and set up animation
    bool loadFromFile(const std::string& filename, 
                      const sf::Vector2u& frameSize, 
                      unsigned int frameCount,
                      float animationSpeed = 10.0f) {
        if (!texture.loadFromFile(filename)) {
            return false;
        }
        
        this->frameSize = frameSize;
        this->frameCount = frameCount;
        this->animationSpeed = animationSpeed;
        this->currentFrame = 0;
        this->frameTime = 0.0f;
        
        sprite = sf::Sprite(texture);
        updateTextureRect();
        
        return true;
    }
    
    // Update animation based on delta time
    void update(float deltaTime) {
        if (!isPlaying || frameCount == 0 || !sprite.has_value()) return;
        
        frameTime += deltaTime;
        float timePerFrame = 1.0f / animationSpeed;
        
        if (frameTime >= timePerFrame) {
            frameTime -= timePerFrame;
            currentFrame++;
            
            if (currentFrame >= frameCount) {
                if (loop) {
                    currentFrame = 0;
                } else {
                    currentFrame = frameCount - 1;
                    isPlaying = false;
                }
            }
            
            updateTextureRect();
        }
    }
    
    // Set the current frame manually
    void setFrame(unsigned int frame) {
        if (frame < frameCount) {
            currentFrame = frame;
            updateTextureRect();
        }
    }
    
    // Play the animation
    void play() {
        isPlaying = true;
    }
    
    // Pause the animation
    void pause() {
        isPlaying = false;
    }
    
    // Stop and reset animation
    void stop() {
        isPlaying = false;
        currentFrame = 0;
        frameTime = 0.0f;
        updateTextureRect();
    }
    
    // Set animation speed (frames per second)
    void setAnimationSpeed(float speed) {
        animationSpeed = speed;
    }
    
    // Set whether to loop
    void setLoop(bool shouldLoop) {
        loop = shouldLoop;
    }
    
    // Set position
    void setPosition(const sf::Vector2f& position) {
        if (sprite.has_value()) {
            sprite->setPosition(position);
        }
    }
    
    // Get position
    sf::Vector2f getPosition() const {
        if (sprite.has_value()) {
            return sprite->getPosition();
        }
        return sf::Vector2f(0, 0);
    }
    
    // Set scale (useful for flipping horizontally)
    void setScale(const sf::Vector2f& scale) {
        if (sprite.has_value()) {
            sprite->setScale(scale);
        }
    }
    
    // Get the underlying sprite for drawing
    const sf::Sprite& getSprite() const {
        return sprite.value();
    }
    
private:
    // Update the texture rectangle to show the current frame
    void updateTextureRect() {
        if (!sprite.has_value()) return;
        
        unsigned int framesPerRow = texture.getSize().x / frameSize.x;
        unsigned int row = currentFrame / framesPerRow;
        unsigned int col = currentFrame % framesPerRow;
        
        sf::IntRect rect;
        rect.position = sf::Vector2i(col * frameSize.x, row * frameSize.y);
        rect.size = sf::Vector2i(frameSize.x, frameSize.y);
        
        sprite->setTextureRect(rect);
    }
};



// Check collision between player and platform
bool checkCollision(const Player& player, const Platform& platform) {
    sf::FloatRect playerBounds = player.shape.getGlobalBounds();
    sf::FloatRect platformBounds = platform.shape.getGlobalBounds();
    
    // Manual AABB collision detection
    return (playerBounds.position.x < platformBounds.position.x + platformBounds.size.x &&
            playerBounds.position.x + playerBounds.size.x > platformBounds.position.x &&
            playerBounds.position.y < platformBounds.position.y + platformBounds.size.y &&
            playerBounds.position.y + playerBounds.size.y > platformBounds.position.y);
}

// Handle player-platform collision
void handleCollision(Player& player, const Platform& platform) {
    sf::FloatRect playerBounds = player.shape.getGlobalBounds();
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
        player.shape.setPosition(sf::Vector2f(playerLeft, platformTop - playerHeight));
        player.velocity.y = 0;
        player.onGround = true;
    }
    // Check if player hits platform from below
    else if (playerTop >= platformTop + platformHeight - 10 && 
             player.velocity.y < 0) {
        player.shape.setPosition(sf::Vector2f(playerLeft, platformTop + platformHeight));
        player.velocity.y = 0;
    }
    // Check side collisions
    else if (playerLeft < platformLeft + platformWidth / 2) {
        // Hit from left
        player.shape.setPosition(sf::Vector2f(platformLeft - playerWidth, playerTop));
        player.velocity.x = 0;
    }
    else {
        // Hit from right
        player.shape.setPosition(sf::Vector2f(platformLeft + platformWidth, playerTop));
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
    player.loadFromFile("images/transparent.png");
    
    
    // Create platforms
    std::vector<Platform> platforms;
    platforms.push_back(Platform(0, 550, 800, 50));      // Ground
    platforms.push_back(Platform(200, 500, 150, 20));   // Platform 1
    platforms.push_back(Platform(400, 350, 150, 20));   // Platform 2
    platforms.push_back(Platform(600, 250, 150, 20));   // Platform 3
    
    // Create animated sprite
    // Example: If your spritesheet has frames that are 64x64 pixels and 8 frames total
    AnimatedSprite animatedSprite;
    if (animatedSprite.loadFromFile("images/spritesheet.png", 
                                     sf::Vector2u(64, 64),  // Frame size (width, height)
                                     8,                     // Number of frames
                                     8.0f)) {               // Animation speed (frames per second)
        animatedSprite.setPosition(sf::Vector2f(400, 300)); // Set initial position
        animatedSprite.setLoop(true);                        // Loop the animation
    }

    
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
        
        // Update animated sprite
        animatedSprite.update(deltaTime);
        
        // Check collisions with all platforms
        for (auto& platform : platforms) {
            if (checkCollision(player, platform)) {
                handleCollision(player, platform);
            }
        }
        
        // Keep player in bounds (optional)
        if (player.shape.getPosition().x < 0) {
            player.shape.setPosition(sf::Vector2f(0, player.shape.getPosition().y));
        }
        if (player.shape.getPosition().x + player.shape.getSize().x > 800) {
            player.shape.setPosition(sf::Vector2f(800 - player.shape.getSize().x, player.shape.getPosition().y));
        }
        
        // Clear screen
        window.clear(sf::Color(135, 206, 235)); // Sky blue background
        
        // Draw platforms
        for (auto& platform : platforms) {
            window.draw(platform.shape);
        }
        
        // Draw player
        window.draw(player.shape);
        
        // Draw animated sprite
        window.draw(animatedSprite.getSprite());
        
        
        // Display everything
        window.display();
    }
    
    return 0;
}
