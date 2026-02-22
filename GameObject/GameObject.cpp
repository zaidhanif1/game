#include "GameObject.h"

GameObject::GameObject(sf::Vector2f p, sf::Vector2f v, sf::Vector2f fs, sf::Vector2f hb)
{   
    this->position = p;
    this->velocity = v;
    this->framesize = fs;
    this->hit_box_dimensions= hb;
}
