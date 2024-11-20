#ifndef ARM_H
#define ARM_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "arm_segment.h"

class Arm 
{
public:
    Arm(const sf::Vector2f& basePosition, int numSegments, float segmentLength);

    void update(const sf::Vector2f& target);
    void draw(sf::RenderWindow& window);

    float PI = 3.14159f;

private:
    std::vector<ArmSegment> segments;
    sf::Vector2f base;
    float totalLength;

    void performCCD(const sf::Vector2f& target);
};

#endif 
