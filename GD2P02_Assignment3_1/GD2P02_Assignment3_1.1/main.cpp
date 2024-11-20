#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "grass_field.h"
#include <cmath>
#include <cstdlib>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Grass Simulation");
    GrassField grassField(200, 800.0f, 560.0f); // Base embedded into the "ground"

    sf::RectangleShape ground(sf::Vector2f(800.0f, 50.0f));
    ground.setFillColor(sf::Color(100, 50, 0));
    ground.setPosition(0.0f, 550.0f);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();
        float elapsedTime = clock.getElapsedTime().asSeconds();

        // Update wind strength for swaying effect
        float windStrength = std::sin(elapsedTime * 0.8f) * 3.0f;

        grassField.update(deltaTime, windStrength);

        window.clear(sf::Color::Black);
        window.draw(ground);
        grassField.render(window);
        window.display();
    }

    return 0;
}
