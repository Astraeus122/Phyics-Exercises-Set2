#include "arm_segment.h"
#include <cmath>

ArmSegment::ArmSegment(float length, float angle, float minAngle, float maxAngle)
    : length(length), angle(angle), minAngle(minAngle), maxAngle(maxAngle), startPosition(0.0f, 0.0f) {}

void ArmSegment::setLength(float length)
{
    this->length = length;
}

float ArmSegment::getLength() const
{
    return length;
}

void ArmSegment::setAngle(float angle)
{
    // Clamp the angle between minAngle and maxAngle
    if (angle < minAngle)
    {
        angle = minAngle;
    }
    else if (angle > maxAngle)
    {
        angle = maxAngle;
    }
    this->angle = angle;
}

float ArmSegment::getAngle() const
{
    return angle;
}

void ArmSegment::setMinAngle(float minAngle)
{
    this->minAngle = minAngle;
}

void ArmSegment::setMaxAngle(float maxAngle)
{
    this->maxAngle = maxAngle;
}

float ArmSegment::getMinAngle() const
{
    return minAngle;
}

float ArmSegment::getMaxAngle() const
{
    return maxAngle;
}

sf::Vector2f ArmSegment::getStartPosition() const
{
    return startPosition;
}

void ArmSegment::setStartPosition(const sf::Vector2f& pos)
{
    startPosition = pos;
}

sf::Vector2f ArmSegment::getEndPosition() const
{
    return sf::Vector2f
    (
        startPosition.x + length * std::cos(angle),
        startPosition.y + length * std::sin(angle)
    );
}
