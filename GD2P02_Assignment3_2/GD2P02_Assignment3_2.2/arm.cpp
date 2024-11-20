#include "arm.h"
#include <cmath>

Arm::Arm(const sf::Vector2f& basePosition, int numSegments, float segmentLength)
    : base(basePosition), totalLength(numSegments* segmentLength)
{
    for (int i = 0; i < numSegments; ++i)
    {
        segments.emplace_back(segmentLength);
    }

    // Initialize positions and angles
    sf::Vector2f currentPos = base;
    float currentAngle = 0.0f;
    for (auto& segment : segments)
    {
        segment.setStartPosition(currentPos);
        segment.setAngle(currentAngle);
        currentPos = segment.getEndPosition();
    }
}

void Arm::update(const sf::Vector2f& target)
{
    performCCD(target);

    // Update positions based on angles
    sf::Vector2f currentPos = base;
    for (auto& segment : segments)
    {
        segment.setStartPosition(currentPos);
        currentPos = segment.getEndPosition();
    }
}

void Arm::draw(sf::RenderWindow& window)
{
    // Draw segments as rectangles
    for (auto& segment : segments)
    {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(segment.getLength(), 10.0f)); // 10.0f is the thickness
        rect.setFillColor(sf::Color::White);
        rect.setOrigin(0.0f, 5.0f); // Set origin to the start of the rectangle
        rect.setPosition(segment.getStartPosition());
        rect.setRotation(segment.getAngle() * 180.0f / PI); // Convert radians to degrees
        window.draw(rect);
    }

    // Draw joints
    for (auto& segment : segments)
    {
        sf::CircleShape joint(5.0f);
        joint.setFillColor(sf::Color::Blue);
        joint.setOrigin(5.0f, 5.0f);
        joint.setPosition(segment.getStartPosition());
        window.draw(joint);
    }

    // Draw end effector
    sf::CircleShape endEffector(7.0f);
    endEffector.setFillColor(sf::Color::Green);
    endEffector.setOrigin(7.0f, 7.0f);
    endEffector.setPosition(segments.back().getEndPosition());
    window.draw(endEffector);
}

void Arm::performCCD(const sf::Vector2f& target)
{
    const float threshold = 1.0f;    // Threshold for proximity to target
    const int maxIterations = 10;     // Maximum iterations per update
    const float damping = 0.5f;       // Damping factor for smoothness
    const float maxDelta = 0.1f;      // Maximum angle change per update

    // Check if the target is within reach
    float distance = std::sqrt(std::pow(target.x - base.x, 2) + std::pow(target.y - base.y, 2));
    if (distance > totalLength)
    {
        // Stretch towards the target if unreachable
        float angle = std::atan2(target.y - base.y, target.x - base.x);
        for (auto& segment : segments)
        {
            segment.setAngle(angle);
        }
        return;
    }

    // Perform CCD iterations
    for (int iteration = 0; iteration < maxIterations; ++iteration)
    {
        // Iterate from the last segment to the first
        for (int i = segments.size() - 1; i >= 0; --i)
        {
            // Get current end effector position
            sf::Vector2f end = segments.back().getEndPosition();

            // Vector from current joint to end effector
            sf::Vector2f r1 = end - segments[i].getStartPosition();

            // Vector from current joint to target
            sf::Vector2f r2 = target - segments[i].getStartPosition();

            // Calculate angles
            float angle1 = std::atan2(r1.y, r1.x);
            float angle2 = std::atan2(r2.y, r2.x);

            // Calculate the angle difference
            float deltaAngle = angle2 - angle1;

            // Normalize the delta angle to be within -PI to PI
            while (deltaAngle > PI) deltaAngle -= 2 * PI;
            while (deltaAngle < -PI) deltaAngle += 2 * PI;

            // Apply damping
            deltaAngle *= damping;

            // Clamp the delta angle to prevent large jumps
            if (deltaAngle > maxDelta)
                deltaAngle = maxDelta;
            else if (deltaAngle < -maxDelta)
                deltaAngle = -maxDelta;

            // Update the segment's angle
            segments[i].setAngle(segments[i].getAngle() + deltaAngle);

            // Update positions of all segments
            sf::Vector2f currentPos = base;
            for (auto& segment : segments)
            {
                segment.setStartPosition(currentPos);
                currentPos = segment.getEndPosition();
            }

            // Check if the end effector is close enough to the target
            float newDistance = std::sqrt(std::pow(segments.back().getEndPosition().x - target.x, 2) +
                std::pow(segments.back().getEndPosition().y - target.y, 2));
            if (newDistance < threshold)
            {
                return;  // Close enough; no need for further iterations
            }
        }
    }
}
