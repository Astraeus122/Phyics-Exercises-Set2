#ifndef ARM_SEGMENT_H
#define ARM_SEGMENT_H

#include <SFML/Graphics.hpp>

class ArmSegment
{
public:
    ArmSegment(float length, float angle = 0.0f, float minAngle = -3.14f, float maxAngle = 3.14f);

    void setLength(float length);
    float getLength() const;

    void setAngle(float angle);
    float getAngle() const;

    void setMinAngle(float minAngle);
    void setMaxAngle(float maxAngle);
    float getMinAngle() const;  // Getter for min angle
    float getMaxAngle() const;  // Getter for max angle

    sf::Vector2f getStartPosition() const;
    void setStartPosition(const sf::Vector2f& pos);

    sf::Vector2f getEndPosition() const;

private:
    float length;
    float angle; // In radians
    float minAngle;
    float maxAngle;
    sf::Vector2f startPosition;
};

#endif
