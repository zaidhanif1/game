#include <SFML/Graphics.hpp>
#include <Animation.h>
#include <string>

    
    Animation::Animation() : frameCount(0), currentFrame(0), fps(5.0f), 
                       frameTime(0.0f), isPlaying(true), loop(true) {
        // Sprite will be initialized when texture is loaded
    }
    
    // Load texture and set up animation
    bool Animation::loadFromFile(const std::string& filename, 
                      const sf::Vector2u& frameSize, 
                      unsigned int frameCount,
                      float fps = 5.0f) 
    {
        if (!texture.loadFromFile(filename)) {
            return false;
        }
        
        this->frameSize = frameSize;
        this->frameCount = frameCount;
        this->fps = fps;
        this->currentFrame = 0;
        this->frameTime = 0.0f;
        
        sprite = sf::Sprite(texture);
        updateTextureRect();
        
        return true;
    }
    
    // Update animation based on delta time
    void Animation::update(float deltaTime) 
    {
        if (!isPlaying || frameCount == 0 || !sprite.has_value()) return; // Nothing to update
        
        frameTime += deltaTime;
        float timePerFrame = 1.0f / fps;
        
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
    void Animation::setFrame(unsigned int frame) 
    {
        if (frame < frameCount) {
            currentFrame = frame;
            updateTextureRect();
        }
    }
    
    // Play the animation
    void Animation::play() 
    {
        isPlaying = true;
    }
    
    // Pause the animation
    void Animation::pause() 
    {
        isPlaying = false;
    }
    
    // Stop and reset animation
    void Animation::stop() 
    {
        isPlaying = false;
        currentFrame = 0;
        frameTime = 0.0f;
        updateTextureRect();
    }
    
    // Set animation speed (frames per second)
    void Animation::setfps(float speed) 
    {
        fps = speed;
    }
    
    // Set whether to loop
    void Animation::setLoop(bool shouldLoop) 
    {
        loop = shouldLoop;
    }
    
    // Set position
    void Animation::setPosition(const sf::Vector2f& position) 
    {
        if (sprite.has_value()) {
            sprite->setPosition(position);
        }
    }
    
    // Get position
    sf::Vector2f Animation::getPosition() const 
    {
        if (sprite.has_value()) {
            return sprite->getPosition();
        }
        return sf::Vector2f(0, 0);
    }
    
    // Set scale (useful for flipping horizontally)
    void Animation::setScale(const sf::Vector2f& scale) 
    {
        if (sprite.has_value()) {
            sprite->setScale(scale);
        }
    }
    
    // Get the underlying sprite for drawing
    const sf::Sprite& Animation::getSprite() const 
    {
        return sprite.value();
    }
    
private:
    // Update the texture rectangle to show the current frame
    void Animation::updateTextureRect() 
    {
        if (!sprite.has_value()) return;
        
        unsigned int framesPerRow = texture.getSize().x / frameSize.x;
        unsigned int row = currentFrame / framesPerRow;
        unsigned int col = currentFrame % framesPerRow;
        
        sf::IntRect rect;
        rect.position = sf::Vector2i(col * frameSize.x, row * frameSize.y);
        rect.size = sf::Vector2i(frameSize.x, frameSize.y);
        
        sprite->setTextureRect(rect);
    }
