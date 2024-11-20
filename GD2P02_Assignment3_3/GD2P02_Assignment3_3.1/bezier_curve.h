#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <SFML/Graphics.hpp>
#include "control_point.h"
#include <vector>

class BezierCurve
{
public:
    BezierCurve(const ControlPoint& p0, const ControlPoint& p1,
        const ControlPoint& p2, const ControlPoint& p3,
        unsigned int resolution = 100);

    void draw(sf::RenderWindow& window) const;
    void update();
    void setResolution(unsigned int resolution);

private:
    const ControlPoint& p0;
    const ControlPoint& p1;
    const ControlPoint& p2;
    const ControlPoint& p3;
    unsigned int resolution;
    std::vector<sf::Vertex> vertices;

    sf::Vector2f calculatePoint(float t) const;
    void generateCurve();
};

#endif // BEZIER_CURVE_H
