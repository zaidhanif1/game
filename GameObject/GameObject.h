#include <SFML/Graphics.hpp>
#include "../Animation/Animation.h"


class GameObject
{
    public:
    GameObject(sf::Vector2f p, sf::Vector2f v, sf::Vector2f fs, sf::Vector2f hb);
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f framesize;
    sf::Vector2f hit_box_dimensions;
    

    /* constants */
    const float GRAVITY = 980.f;


    private:
    /* data */
};

