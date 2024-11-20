#include "grass_blade.h"
#include <cmath>
#include <cstdlib>

GrassBlade::GrassBlade(float baseX, float baseY, float maxLength)
    : base(baseX, baseY), length(maxLength), swayAngle(0.0f)
{
    swaySpeed = static_cast<float>(rand()) / RAND_MAX * 0.5f + 0.2f; // Speed range for grass offset
    varianceOffset = static_cast<float>(rand()) / RAND_MAX * 6.28f;  // Random offset for phase (0 to 2*PI)

    // Initial call to calculateSegments with an initial sway value
    float initialSway = std::sin(varianceOffset) * 0.5f; // Use varianceOffset to create an initial sway
    calculateSegments(initialSway);
}

// Update GrassBlade update and calculateSegments methods
void GrassBlade::update(float deltaTime, float windStrength)
{
    // Update sway angle continuously for a smooth effect
    swayAngle += swaySpeed * deltaTime; // Accumulate sway speed over time to create oscillating movement

    // Apply wind strength to influence the sway dynamically
    float windEffect = windStrength * 0.2f; // Influence of wind on the grass, adjusted for effect magnitude
    float totalSway = std::sin(swayAngle + varianceOffset) * 0.5f + windEffect;

    // Calculate the segments based on new total sway
    calculateSegments(totalSway);
}

void GrassBlade::calculateSegments(float sway)
{
    segments.clear();
    Vector2 currentPosition = base; // Start at the base position

    int numSegments = 5;  // Number of segments for each blade of grass
    float segmentLength = length / static_cast<float>(numSegments);
    float currentAngle = sway; // Start with the sway at the base

    for (int i = 0; i < numSegments; ++i)
    {
        // Calculate the position of the next segment with left/right swaying
        Vector2 nextPosition = currentPosition + Vector2
        (
            std::sin(currentAngle) * segmentLength,  // Horizontal sway
            -segmentLength                           // Upward growth
        );

        segments.push_back(nextPosition);
        currentPosition = nextPosition;

        // Gradually increase the sway effect as we move up the blade
        currentAngle += sway * 0.3f; // Gradually amplify the angle at each segment for more tip movement
    }
}

std::vector<Vector2> GrassBlade::getSegments() const
{
    return segments;
}
