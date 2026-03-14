#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Animation/Animation.h"
#include "../GameObject/GameObject.h"

enum class PlayerState 
{
    IDLE,  ///< Player is standing still
    WALK,  ///< Player is walking
    RUN,   ///< Player is running
    JUMP,  ///< Player is jumping or in the air
};


class Player : public GameObject
{
public:
    
    Player(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f frame_size, sf::Vector2f hit_box_dimensions);
    
    Animation idleAnimation;
    Animation walkAnimation;
    Animation runAnimation;
    Animation jumpAnimation;
    Animation* currentAnimation;

    PlayerState currentState;
    
    
    const float WALK_SPEED = 200.0f;
    const float RUN_SPEED = 350.0f;
    const std::string base_path = "assets/Player/";
    
    bool load_all_animations();
    bool load_animation(Animation& anim, const std::string& filePath, 
                       const sf::Vector2f& frameSize, 
                       unsigned int frameCount, 
                       float fps);
    
    void update(float deltaTime);
    void jump();
    sf::FloatRect getGlobalBounds() const;
    
    void setPosition(const sf::Vector2f& pos);
    const sf::Sprite& getSprite();
    void updateAnimationState();
    void updateAnimation(float deltaTime);
    
private:
    void setAnimation(PlayerState newState);
};
