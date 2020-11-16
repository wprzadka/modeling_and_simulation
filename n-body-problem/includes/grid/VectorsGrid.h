//
// Created by viking on 10.11.2020.
//

#ifndef N_BODY_PROBLEM_VECTORSGRID_H
#define N_BODY_PROBLEM_VECTORSGRID_H

#include "Grid.h"

class VectorsGrid : public Grid {

    std::vector<std::vector<sf::Vertex>> vertices;
    float unitDistance;
    sf::Color color;
    float forceMultiplier;

public:
    VectorsGrid(std::pair<float, float> window_size, float distance, sf::Color color = sf::Color::White,
                float multiplier = 10.f);
    ~VectorsGrid() = default;

    virtual void update(const std::vector<Body>&);
    virtual void draw(sf::RenderWindow& window);
};


#endif //N_BODY_PROBLEM_VECTORSGRID_H
