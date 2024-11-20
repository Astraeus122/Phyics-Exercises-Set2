#include <SFML/Graphics.hpp>
#include "arm.h"
#include <iostream>

int main()
{
    // Window setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Inverse Kinematics Arm");
    window.setFramerateLimit(60);

    // Arm setup
    sf::Vector2f basePosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    int numSegments = 5;
    float segmentLength = 50.0f;
    Arm arm(basePosition, numSegments, segmentLength);

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

        // Update arm
        arm.update(target);

        // Rendering
        window.clear(sf::Color::Black);
        arm.draw(window);
        window.display();
    }

    return 0;
}
