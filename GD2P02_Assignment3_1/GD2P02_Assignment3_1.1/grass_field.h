#ifndef GRASS_FIELD_H
#define GRASS_FIELD_H

#include <vector>
#include "grass_blade.h"
#include <SFML/Graphics.hpp>

class GrassField 
{
public:
    GrassField(int numBlades, float windowWidth, float baseY);

    void update(float deltaTime, float windStrength);
    void render(sf::RenderWindow& window);
    std::vector<GrassBlade> grassBlades;

private:
    std::vector<GrassBlade> blades;
};

#endif