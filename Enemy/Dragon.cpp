#include "Dragon.h"
#include "Enemy.h"

Dragon::Dragon(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f frame_size, sf::Vector2f hit_box_dimensions)
    :
Enemy(position, velocity, frame_size, hit_box_dimensions)
    {
        this->dragon_facing_right = true;
        this->dragon_state = DragonState::DRAGON_IDLE;   
    }

bool Dragon::load_dragon_animations()
{   
    bool success = true;

    success &= this->dragon_idle.loadFromFile(base_path + "Idle.png", this->frameSize, DRAGON_IDLE_FRAME_COUNT, 8.0, this->position);

    
    return success;
}
