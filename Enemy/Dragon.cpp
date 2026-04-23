#include "Dragon.h"
#include "Enemy.h"

Dragon::Dragon(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f frame_size, sf::Vector2f hit_box_dimensions)
    :
Enemy(position, velocity, frame_size, hit_box_dimensions)
    {
        this->dragon_facing_right = true;
        this->dragon_state = DragonState::DRAGON_IDLE;
        this->curr_animation = nullptr;
    }

bool Dragon::load_dragon_animations()
{   
    bool success = true;

    success &= this->dragon_idle.loadFromFile(base_path + "Idle.png", this->framesize, DRAGON_IDLE_FRAME_COUNT, 8.0, this->position);

    if (!success) return false;

    curr_animation = &dragon_idle;
    dragon_idle.play();

    return success;
}

void Dragon::draw(sf::RenderWindow& window)
{
    if (curr_animation)
    {
        window.draw(curr_animation->getSprite());
        return;
    }
    window.draw(dragon_idle.getSprite());    
}

void Dragon::onLateUpdate(float delta_time)
{
    updateDragonAnimationState();
    updateAnimation(delta_time);
}

void Dragon::updateDragonAnimationState()
{
    DragonState currstate = dragon_state;
    setDragonState(currstate);

}

void Dragon::updateAnimation(float delta_time)
{
    if (curr_animation)
    {
        curr_animation->update(delta_time);
    }
}
void Dragon::setDragonState(DragonState state)
{
    
    switch(state)
    {
        case DragonState::DRAGON_IDLE:
            curr_animation = &dragon_idle;
            break;
        case DragonState::DRAGON_ATTACK:
            curr_animation = &dragon_attack;
            break;
        default:
            curr_animation = &dragon_idle;
            break;
    }
    return;
}