#include "segment.h"

Segment::Segment(float length, const sf::Vector2f& position)
    : length(length), position(position) {}

void Segment::setPosition(const sf::Vector2f& pos)
{
    position = pos;
}

const sf::Vector2f& Segment::getPosition() const
{
    return position;
}

float Segment::getLength() const
{
    return length;
}
