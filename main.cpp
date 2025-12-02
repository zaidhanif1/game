#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <cstring>

enum directions{ down, right, up, left };
int main()
{
    unsigned int width = 640;
    unsigned int height = 360;

    std::cout << std::filesystem::current_path() << std::endl;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({width, height}), "Window");
    window.setFramerateLimit(120.0f);

    sf::Texture texture;

    if(!texture.loadFromFile("assets/GiantBat.png"));
    {
        std::cerr << "Failed to load texture: " << strerror(errno) << "\n";
        return -1;
    }
    
    sf::Sprite sprite(texture); //loading texture onto sprite

    sprite.setOrigin( {texture.getSize().x / 2.0f, texture.getSize().y / 2.0f} );
    sprite.setPosition( { width/2.0f, height / 2.0f } );


    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            
        // Clear screen
        window.clear();

        //Drawing
        window.draw(sprite);
        // Update the window
        window.display();
    }
}
}