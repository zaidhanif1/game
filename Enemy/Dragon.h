#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "../GameObject/GameObject.h"
#include "../Animation/Animation.h"

#define DRAGON_IDLE_FRAME_COUNT 3
enum class DragonState
{
    DRAGON_IDLE,
    DRAGON_WALK, 
    DRAGON_RUN,
    DRAGON_ATTACK, 
    DRAGON_DEATH
};
class Dragon : public Enemy
{
    public:
        Dragon(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f frame_size, sf::Vector2f hit_box_dimensions);

        std::string base_path = "assets/Enemies/dragon/";
        DragonState dragon_state;
        bool dragon_facing_right;
        bool load_dragon_animations();

        Animation dragon_attack;
        Animation dragon_idle;
        Animation dragon_run;
        Animation dragon_death;

};
