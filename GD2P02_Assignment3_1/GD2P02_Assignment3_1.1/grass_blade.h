#ifndef GRASS_BLADE_H
#define GRASS_BLADE_H

#include <vector>
#include "Vector2.h"

class GrassBlade
{
public:
    GrassBlade(float baseX, float baseY, float maxLength);

    void update(float deltaTime, float windStrength);
    void calculateSegments(float sway);
    std::vector<Vector2> getSegments() const;

private:

    std::vector<Vector2> segments;
    Vector2 base;
    float length;
    float swayAngle;
    float swaySpeed;
    float varianceOffset;
};

#endif