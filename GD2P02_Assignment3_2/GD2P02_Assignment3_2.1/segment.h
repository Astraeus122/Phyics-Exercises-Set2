#ifndef SEGMENT_H
#define SEGMENT_H

#include <SFML/Graphics.hpp>

class Segment
{
public:
    Segment(float length, const sf::Vector2f& position);

    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;

    float getLength() const;

private:
    sf::Vector2f position;
    float length;
};

#endif 
