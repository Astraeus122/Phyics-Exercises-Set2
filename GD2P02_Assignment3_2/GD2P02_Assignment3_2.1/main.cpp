#include <SFML/Graphics.hpp>
#include "worm.h"

int main()
{
    // Window setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Inverse Kinematics Worm");
    window.setFramerateLimit(60);

    // Initialize the worm
    int numSegments = 15;
    float segmentLength = 30.0f;
    sf::Vector2f startPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    Worm worm(numSegments, segmentLength, startPosition);

    while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Update the worm to follow the mouse
        worm.follow(target);

        // Rendering
        window.clear(sf::Color::Black);
        worm.draw(window);
        window.display();
    }

    return 0;
}
