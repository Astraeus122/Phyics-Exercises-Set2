#ifndef WORM_H
#define WORM_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "segment.h"

class Worm
{
public:
    Worm(int numSegments, float segmentLength, const sf::Vector2f& startPosition);

    void follow(const sf::Vector2f& target);
    void draw(sf::RenderWindow& window);

private:
    std::vector<Segment> segments;
    float totalLength;
};

#endif 
