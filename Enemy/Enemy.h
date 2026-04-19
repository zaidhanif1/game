#pragma once
#include  "../Animation/Animation.h"
#include <SFML/Graphics.hpp>
#include "../GameObject/GameObject.h"


enum class EnemyType
{
    DRAGON,
    DEMON,
    MEDUSA
};


// struct Dragon
// {
//     sf::Vector2f position;
//     sf::Vector2f velocity;
//     Animation idle;
//     Animation walk;
//     Animation attack;
//     Animation death;
//     sf::Vector2u frameSize;
//     Animation* current;
//     EnemyState state;
//     bool onGround;
    
// };



class Enemy : public GameObject
{
    public:
        Enemy(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f frame_size, sf::Vector2f hit_box_dimensions);
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f frameSize;
        Animation idleAnimation;
        Animation attackingAnimation;
        Animation deadAnimation;

        bool load_dragon(struct Dragon& d);
        int frameSizeX = 96;
        int frameSizeY = 70;
        const std::string &basePath = "assets/Enemies/";
        bool loadAnimation(EnemyType type);
        void update(float deltaTime, EnemyType type);
        const sf::Sprite& getSprite(EnemyType type);
        const float GRAVITY = 980.0f;
        
};