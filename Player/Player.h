#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Animation/Animation.h"

/**
 * @enum PlayerState
 * @brief Represents the current state/animation of the player
 */
enum class PlayerState 
{
    IDLE,  ///< Player is standing still
    WALK,  ///< Player is walking
    RUN,   ///< Player is running
    JUMP,  ///< Player is jumping or in the air
};

/**
 * @class Player
 * @brief Represents the player character with physics, animations, and movement
 * 
 * This class manages the player's position, velocity, animations, and state.
 * It handles gravity, jumping, movement, and animation state transitions
 * based on the player's current movement and ground status.
 * 
 * @note The player uses center-based positioning for proper sprite flipping.
 *       All animations share the same position and are kept in sync.
 * 
 * @example
 * @code
 * Player player(100, 100);
 * player.loadAnimations();
 * 
 * // In game loop:
 * player.update(deltaTime);
 * player.updateAnimationState();
 * player.updateAnimation(deltaTime);
 * window.draw(player.getSprite());
 * @endcode
 */
class Player 
{
public:
    /**
     * @brief Constructs a player at the specified position
     * 
     * Initializes the player with default values and sets all animations
     * to the starting position. The player starts in IDLE state.
     * 
     * @param x Initial X position (center point)
     * @param y Initial Y position (center point)
     */
    Player(float x, float y);

    /// @name Animation Members
    /// @{
    
    /** @brief Animation for idle state */
    Animation idleAnimation;
    
    /** @brief Animation for walking state */
    Animation walkAnimation;
    
    /** @brief Animation for running state */
    Animation runAnimation;
    
    /** @brief Animation for jumping/airborne state */
    Animation jumpAnimation;
    
    /** @brief Pointer to the currently active animation */
    Animation* currentAnimation;
    
    /** @brief Current player state determining which animation plays */
    PlayerState currentState;
    
    /// @}
    
    /// @name Physics and State Members
    /// @{
    
    /** @brief Whether the player is facing right (true) or left (false) */
    bool facingRight;
    
    /** @brief Whether the player is currently on the ground */
    bool onGround;
    
    /** @brief Current position (center point) */
    sf::Vector2f position;
    
    /** @brief Current velocity vector (pixels per second) */
    sf::Vector2f velocity;
    
    /** @brief Size of each animation frame in pixels */
    sf::Vector2u frameSize;
    
    /** @brief Width of each frame in pixels (96 pixels) */
    int frameSizeX = 96;
    /** @brief Height of each frame in pixels (70 pixels) */
    int frameSizeY = 70;

    /** @brief Width of the hitbox in pixels (70 pixels) */
    int hitboxSizeX = 20;
    /** @brief Height of the hitbox in pixels (50 pixels) */
    int hitboxSizeY = 40;
    
    /// @}
    
    /// @name Physics Constants
    /// @{
    
    /** @brief Walking speed in pixels per second */
    const float WALK_SPEED = 200.0f;
    
    /** @brief Running speed in pixels per second */
    const float RUN_SPEED = 350.0f;
    
    /** @brief Gravity acceleration in pixels per second squared */
    const float GRAVITY = 980.0f;
    
    /// @}
    
    /**
     * @brief Loads all player animations from a base directory
     * 
     * Loads IDLE, WALK, RUN, and JUMP animations from the specified path.
     * All animations are configured with appropriate frame counts and FPS.
     * 
     * @param basePath Base directory path containing animation files
     *                 (default: "assets/with_outline/")
     * @return true if all animations loaded successfully, false otherwise
     * 
     * @note Expected files: IDLE.png, WALK.png, RUN.png, JUMP.png
     * @note Sets all animations to loop and starts the idle animation
     */
    bool loadAllAnimations(const std::string& basePath = "assets/with_outline/");
    
    /**
     * @brief Loads a single animation with custom parameters
     * 
     * Helper function to load an animation file with specific frame settings.
     * Preserves position and sets origin to center for proper flipping.
     * 
     * @param anim       Animation object to load into
     * @param filePath   Path to the animation sprite sheet file
     * @param frameSize  Size of each frame in pixels
     * @param frameCount Total number of frames in the animation
     * @param fps        Animation speed in frames per second
     * @return true if the animation loaded successfully, false otherwise
     */
    bool loadAnimation(Animation& anim, const std::string& filePath, 
                       const sf::Vector2u& frameSize, 
                       unsigned int frameCount, 
                       float fps);
    
    /**
     * @brief Updates player physics and position
     * 
     * Applies gravity, updates position based on velocity, handles sprite
     * flipping based on movement direction, and resets onGround flag.
     * 
     * @param deltaTime Time elapsed since last frame in seconds
     * 
     * @note Call this before collision detection. The onGround flag will be
     *       set by the collision system after this update.
     */
    void update(float deltaTime);
    
    /**
     * @brief Makes the player jump if on the ground
     * 
     * Applies upward velocity to initiate a jump. Only works when onGround
     * is true, preventing double jumps.
     */
    void jump();
    
    /**
     * @brief Gets the global bounding rectangle for collision detection
     * 
     * @return Bounding rectangle of the current animation sprite, or empty
     *         rectangle if no animation is loaded
     */
    sf::FloatRect getGlobalBounds() const;
    
    /**
     * @brief Gets the current position of the player
     * 
     * @return Current position (center point), or (0,0) if no animation loaded
     */
    sf::Vector2f getPosition() const;
    
    /**
     * @brief Sets the position of the player
     * 
     * Updates the position of all animations to keep them synchronized.
     * 
     * @param pos New position (center point)
     */
    void setPosition(const sf::Vector2f& pos);
    
    /**
     * @brief Gets the sprite for rendering
     * 
     * Returns the sprite from the currently active animation.
     * 
     * @return Reference to the current animation's sprite
     * @warning Returns idle animation sprite if currentAnimation is null
     */
    const sf::Sprite& getSprite() const;
    
    /**
     * @brief Updates the animation state based on player movement
     * 
     * Determines which animation should play based on velocity and ground
     * status. Priority: JUMP > RUN > WALK > IDLE.
     * 
     * @note Call this AFTER collision detection to ensure onGround is accurate
     * @note Call this BEFORE updateAnimation() to avoid animation flashing
     */
    void updateAnimationState();
    
    /**
     * @brief Updates the current animation frame
     * 
     * Advances the current animation based on elapsed time.
     * 
     * @param deltaTime Time elapsed since last frame in seconds
     * 
     * @note Call this AFTER updateAnimationState() to ensure the correct
     *       animation is being updated
     */
    void updateAnimation(float deltaTime);
    
private:
    /**
     * @brief Switches to a specific animation state
     * 
     * Changes the current animation and resets it to the first frame.
     * Only switches if the new state is different from the current state.
     * 
     * @param newState The animation state to switch to
     */
    void setAnimation(PlayerState newState);
};
