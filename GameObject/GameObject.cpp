#include "GameObject.h"

GameObject::GameObject(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f framesize, sf::Vector2f hit_box_dimensions)
{   
    this->position = position;
    this->velocity = velocity;
    this->framesize = framesize;
    this->hit_box_dimensions= hit_box_dimensions;
    onGround = false;
    facing_right = true;
}

bool GameObject::update(float delta_time)
{
    if (!onGround) 
    {
        velocity.y += GRAVITY * delta_time;
    }
    position.x += velocity.x * delta_time;
    position.y += velocity.y * delta_time;

    bool new_facing_right = facing_right;
    if (velocity.x > 0.1f) 
    {
        new_facing_right = true;
    } 
    else if (velocity.x < -0.1f) 
    {
        new_facing_right = false;
    }
    
    onGround = false;
    return new_facing_right;
}

sf::Vector2f GameObject::getPosition() const
{
    return position;
}
