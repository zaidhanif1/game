#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class Player 
{
    public:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::RectangleShape shape;
        sf::Vector2f velocity;
        bool onGround;
        Player(float x, float y);
        void update(float deltaTime);
        void jump();
        void loadFromFile(const std::string& filePath);
        void setSprite();
};