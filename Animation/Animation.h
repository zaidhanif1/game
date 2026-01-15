#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

/**
 * @class Animation
 * @brief Handles sprite sheet animations for SFML 3.0
 * 
 * This class manages frame-based animations from a sprite sheet texture.
 * It supports variable frame rates, looping, and standard playback controls.
 * 
 * @note SFML 3.0 requires a texture at sprite construction, so the sprite
 *       is stored as std::optional and created when loadFromFile() is called.
 * 
 * @example
 * @code
 * Animation walkAnim;
 * walkAnim.loadFromFile("walk.png", {64, 64}, 8, 12.0f);
 * walkAnim.play();
 * 
 * // In game loop:
 * walkAnim.update(deltaTime);
 * window.draw(walkAnim.getSprite());
 * @endcode
 */
class Animation
{
public:
    /**
     * @brief Default constructor
     * 
     * Initializes animation properties to default values.
     * The sprite is not created until loadFromFile() is called.
     */
    Animation();

    /**
     * @brief Loads a sprite sheet and configures the animation
     * 
     * @param filename   Path to the sprite sheet image file
     * @param frameSize  Size of each individual frame in pixels (width, height)
     * @param frameCount Total number of frames in the animation
     * @param fps        Animation speed in frames per second (default: 10.0)
     * @return true if the texture was loaded successfully, false otherwise
     * 
     * @note Frames are read left-to-right, top-to-bottom from the sprite sheet
     */
    bool loadFromFile(const std::string& filename, 
                      const sf::Vector2u& frameSize, 
                      unsigned int frameCount,
                      float fps = 10.0f);

    /**
     * @brief Updates the animation based on elapsed time
     * 
     * Call this every frame with the delta time to advance the animation.
     * Automatically handles frame switching based on the configured FPS.
     * 
     * @param deltaTime Time elapsed since the last frame in seconds
     */
    void update(float deltaTime);

    /**
     * @brief Manually sets the current animation frame
     * 
     * @param frame Frame index to display (0-based, must be < frameCount)
     */
    void setFrame(unsigned int frame);
    
    /**
     * @brief Starts or resumes the animation playback
     */
    void play();

    /**
     * @brief Pauses the animation at the current frame
     */
    void pause();

    /**
     * @brief Stops the animation and resets to the first frame
     */
    void stop();

    /**
     * @brief Sets the animation playback speed
     * 
     * @param speed Frames per second (higher = faster animation)
     */
    void setfps(float speed);


    /**
     * @brief Sets the position of the animation sprite
     * 
     * @param position New position in world coordinates
     */
    void setPosition(const sf::Vector2f& position);

    /**
     * @brief Gets the current position of the animation sprite
     * 
     * @return Current position, or (0,0) if texture not loaded
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Sets the scale of the animation sprite
     * 
     * @param scale Scale factors (use negative values to flip)
     * 
     * @example
     * @code
     * animation.setScale({-1.0f, 1.0f});  // Flip horizontally
     * animation.setScale({2.0f, 2.0f});   // Double size
     * @endcode
     */
    void setScale(const sf::Vector2f& scale);
    
    /**
     * @brief Sets the origin of the sprite (for proper flipping/rotation)
     * 
     * @param origin The origin point relative to the sprite's local bounds
     */
    void setOrigin(const sf::Vector2f& origin);

    /**
     * @brief Gets the underlying sprite for rendering
     * 
     * @return Reference to the internal sf::Sprite
     * @warning Only call after loadFromFile() succeeds, otherwise undefined behavior
     */
    const sf::Sprite& getSprite() const;

    /// @name Public Members
    /// @{
    
    /** @brief The sprite used for rendering (created after texture loads) */
    std::optional<sf::Sprite> sprite;
    
    /** @brief The loaded texture (sprite sheet) */
    sf::Texture texture;    
    
    /** @brief Size of each frame in pixels (width, height) */
    sf::Vector2u frameSize;
    
    /** @brief Total number of frames in the animation */
    unsigned int frameCount;
    
    /** @brief Current frame index (0-based) */
    unsigned int currentFrame;
    
    /** @brief Animation speed in frames per second */
    float fps;
    
    /** @brief Time accumulator for frame switching */
    float frameTime;
    
    /** @brief Whether the animation is currently playing */
    bool isPlaying;
    
    /** @brief Whether the animation loops when it reaches the end */
    bool loop;
    
    /** @brief Whether a texture has been successfully loaded */
    bool textureLoaded;
    
    /// @}

    /**
     * @brief Updates the texture rectangle to display the current frame
     * 
     * Calculates the correct region of the sprite sheet based on
     * currentFrame and frameSize, then applies it to the sprite.
     */
    void updateTextureRect();
};
