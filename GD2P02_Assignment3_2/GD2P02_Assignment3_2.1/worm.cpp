#include "worm.h"
#include <cmath>

// Helper function to calculate distance between two points
float distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

// Helper function to normalize a vector
sf::Vector2f normalize(const sf::Vector2f& v)
{
    float mag = std::sqrt(v.x * v.x + v.y * v.y);
    if (mag == 0)
        return sf::Vector2f(0, 0);
    return sf::Vector2f(v.x / mag, v.y / mag);
}

Worm::Worm(int numSegments, float segmentLength, const sf::Vector2f& startPosition)
    : totalLength(numSegments* segmentLength)
{
    for (int i = 0; i < numSegments; ++i)
    {
        segments.emplace_back(segmentLength, startPosition);
    }
}

void Worm::follow(const sf::Vector2f& target)
{
    // Set the first segment to the target position
    segments[0].setPosition(target);

    // Iterate through each segment to follow the previous one
    for (size_t i = 1; i < segments.size(); ++i)
    {
        sf::Vector2f prev = segments[i - 1].getPosition();
        sf::Vector2f current = segments[i].getPosition();
        sf::Vector2f direction = prev - current;
        float dist = distance(prev, current);
        if (dist != 0)
        {
            direction = normalize(direction);
            segments[i].setPosition(prev - direction * segments[i].getLength());
        }
    }
}

void Worm::draw(sf::RenderWindow& window)
{
    sf::VertexArray lines(sf::LinesStrip, segments.size());
    for (size_t i = 0; i < segments.size(); ++i) {
        lines[i].position = segments[i].getPosition();
        lines[i].color = sf::Color::Green;
    }
    window.draw(lines);
}
