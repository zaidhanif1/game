#include <SFML/Graphics.hpp>
#include <string>




class Animation
{
    public:
        Animation();
        bool loadFromFile(const std::string& filename, 
                          const sf::Vector2u& frameSize, 
                          unsigned int frameCount,
                          float fps = 10.0f);
        void update(float deltaTime);
        void setFrame(unsigned int frame);
        // Play the animation
        void play();
        // Pause the animation
        void pause();
        void stop();
        void setfps(float speed);
        void setLoop(bool shouldLoop);
        void setPosition(const sf::Vector2f& position);
        sf::Vector2f getPosition() const;
        void setScale(const sf::Vector2f& scale);
        const sf::Sprite& getSprite() const;

        std::optional<sf::Sprite> sprite;
        sf::Texture texture;    
        // Animation properties
        sf::Vector2u frameSize;      // Size of each frame (width, height)
        unsigned int frameCount;      // Total number of frames in the animation
        unsigned int currentFrame;    // Current frame index
        float fps;         // Frames per second
        float frameTime;              // Time accumulator for frame switching
        // Animation state
        bool isPlaying;                // Whether animation is playing
        bool loop;                     // Whether to loop the animation

        private:
            void updateTextureRect();
    };