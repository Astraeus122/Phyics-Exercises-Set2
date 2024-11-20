#include "control_point.h"

ControlPoint::ControlPoint(const sf::Vector2f& position, float radius,
    sf::Color normalColor, sf::Color hoveredColor)
    : normalColor(normalColor), hoveredColor(hoveredColor), hovered(false)
{
    shape.setRadius(radius);
    shape.setFillColor(normalColor);
    shape.setOrigin(radius, radius); // Center the circle
    shape.setPosition(position);
}

void ControlPoint::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

bool ControlPoint::isHovered(const sf::Vector2f& mousePos) const
{
    return shape.getGlobalBounds().contains(mousePos);
}

void ControlPoint::setPosition(const sf::Vector2f& position)
{
    shape.setPosition(position);
}

const sf::Vector2f& ControlPoint::getPosition() const
{
    return shape.getPosition();
}

void ControlPoint::setHovered(bool isHovered)
{
    hovered = isHovered;
    if (hovered)
    {
        shape.setFillColor(hoveredColor);
    }
    else
    {
        shape.setFillColor(normalColor);
    }
}

bool ControlPoint::getHovered() const
{
    return hovered;
}

void ControlPoint::setActive(bool isActive)
{
    if (isActive)
    {
        shape.setOutlineThickness(2.0f);
        shape.setOutlineColor(sf::Color::White);
    }
    else
    {
        shape.setOutlineThickness(0.0f);
    }
}

bool ControlPoint::isActive() const
{
    return shape.getOutlineThickness() > 0.0f;
}
