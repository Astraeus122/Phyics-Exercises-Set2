#include "grass_field.h"
#include <cstdlib>

GrassField::GrassField(int numBlades, float windowWidth, float baseY)
{
    numBlades = 400;  // High number of grass blades for a denser field

    float spacing = windowWidth / static_cast<float>(numBlades); // Ensures no overlap between blades

    for (int i = 0; i < numBlades; ++i)
    {
        float xPosition = i * spacing + (static_cast<float>(rand()) / RAND_MAX * (spacing / 2) - spacing / 4); // Random offset within spacing
        float length = static_cast<float>(rand()) / RAND_MAX * 50.0f + 100.0f; // Random length between 100 and 150

        // Lower the baseY to embed the grass deeper
        float adjustedBaseY = baseY + 20.0f; // Lowering the base position by an additional 20 pixels

        grassBlades.push_back(GrassBlade(xPosition, adjustedBaseY, length));
    }
}


void GrassField::update(float deltaTime, float windStrength)
{
    for (GrassBlade& blade : grassBlades)
    {
        blade.update(deltaTime, windStrength);
    }
}

void GrassField::render(sf::RenderWindow& window)
{
    for (const GrassBlade& blade : grassBlades)
    {
        std::vector<Vector2> segments = blade.getSegments();
        for (size_t i = 0; i < segments.size() - 1; ++i)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(segments[i].x, segments[i].y), sf::Color::Green),
                sf::Vertex(sf::Vector2f(segments[i + 1].x, segments[i + 1].y), sf::Color::Green)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}
