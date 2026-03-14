#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "../Animation/Animation.h"


class GameObject
{
    public:
        GameObject(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f framesize, sf::Vector2f hit_box_dimensions);
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f framesize;
        sf::Vector2f hit_box_dimensions;
        bool onGround;
        bool facing_right;

        //functions
        bool update(float delta_time);
        
        sf::Vector2f getPosition() const;


        /* constants */
        const float GRAVITY = 980.f;


        private:
        /* data */
};

#endif // GAMEOBJECT_H

