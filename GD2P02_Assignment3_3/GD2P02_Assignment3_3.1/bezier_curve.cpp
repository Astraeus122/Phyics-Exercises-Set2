#include "bezier_curve.h"
#include <cmath>

BezierCurve::BezierCurve(const ControlPoint& p0, const ControlPoint& p1,
    const ControlPoint& p2, const ControlPoint& p3,
    unsigned int resolution)
    : p0(p0), p1(p1), p2(p2), p3(p3), resolution(resolution)
{
    generateCurve();
}

void BezierCurve::setResolution(unsigned int res)
{
    resolution = res;
    generateCurve();
}

void BezierCurve::update()
{
    generateCurve();
}

void BezierCurve::draw(sf::RenderWindow& window) const
{
    window.draw(vertices.data(), vertices.size(), sf::LineStrip);
}

sf::Vector2f BezierCurve::calculatePoint(float t) const
{
    // Cubic Bezier formula
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    sf::Vector2f point = uuu * p0.getPosition(); // first term
    point += 3 * uu * t * p1.getPosition();      // second term
    point += 3 * u * tt * p2.getPosition();      // third term
    point += ttt * p3.getPosition();             // fourth term

    return point;
}

void BezierCurve::generateCurve()
{
    vertices.clear();
    vertices.reserve(resolution + 1);

    for (unsigned int i = 0; i <= resolution; ++i)
    {
        float t = static_cast<float>(i) / resolution;
        sf::Vector2f point = calculatePoint(t);
        vertices.emplace_back(point, sf::Color::Green);
    }
}
