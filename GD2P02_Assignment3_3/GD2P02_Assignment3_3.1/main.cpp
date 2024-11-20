#include <SFML/Graphics.hpp>
#include "control_point.h"
#include "bezier_curve.h"

int main()
{
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Cubic Bezier Curve");
    window.setFramerateLimit(60);

    // Define anchor points (blue, non-movable)
    ControlPoint anchorLeft(sf::Vector2f(50.0f, windowHeight / 2.0f), 7.0f, sf::Color::Blue, sf::Color::Blue);
    ControlPoint anchorRight(sf::Vector2f(windowWidth - 50.0f, windowHeight / 2.0f), 7.0f, sf::Color::Blue, sf::Color::Blue);

    // Define control points (red and red)
    ControlPoint control1(sf::Vector2f(windowWidth / 3.0f, windowHeight / 3.0f));
    ControlPoint control2(sf::Vector2f(2 * windowWidth / 3.0f, 2 * windowHeight / 3.0f));

    // Create Bezier curve with references to control points
    BezierCurve bezier(anchorLeft, control1, control2, anchorRight);

    // Variables for dragging
    bool isDraggingControl1 = false;
    bool isDraggingControl2 = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDraggingControl1 = true;
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    isDraggingControl2 = true;
                }
            }
            break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDraggingControl1 = false;
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    isDraggingControl2 = false;
                }
                break;

            case sf::Event::MouseMoved:
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                // Update positions if dragging
                if (isDraggingControl1)
                {
                    control1.setPosition(mousePos);
                }
                if (isDraggingControl2)
                {
                    control2.setPosition(mousePos);
                }

                // Update the curve if any control point has moved
                bezier.update();
            }
            break;

            default:
                break;
            }
        }

        // Handle hover states (optional)
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        bool control1Hovered = control1.isHovered(mousePos);
        bool control2Hovered = control2.isHovered(mousePos);

        control1.setHovered(control1Hovered);
        control2.setHovered(control2Hovered);

        window.clear(sf::Color::Black);

        // Draw Bezier curve
        bezier.draw(window);

        // Draw anchor and control points
        anchorLeft.draw(window);
        anchorRight.draw(window);
        control1.draw(window);
        control2.draw(window);

        window.display();
    }

    return 0;
}
