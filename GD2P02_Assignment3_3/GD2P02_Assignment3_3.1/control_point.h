#ifndef CONTROL_POINT_H
#define CONTROL_POINT_H

#include <SFML/Graphics.hpp>

class ControlPoint
{
public:
    ControlPoint(const sf::Vector2f& position, float radius = 5.0f,
        sf::Color normalColor = sf::Color::Red,
        sf::Color hoveredColor = sf::Color::Yellow);

    void draw(sf::RenderWindow& window) const;
    bool isHovered(const sf::Vector2f& mousePos) const;
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;

    void setHovered(bool hovered);
    bool getHovered() const;

    void setActive(bool active);
    bool isActive() const;

private:
    sf::CircleShape shape;
    sf::Color normalColor;
    sf::Color hoveredColor;
    bool hovered;
};

#endif
