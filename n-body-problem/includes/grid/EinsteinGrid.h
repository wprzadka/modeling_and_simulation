//
// Created by viking on 09.11.2020.
//

#ifndef N_BODY_PROBLEM_EINSTEINGRID_H
#define N_BODY_PROBLEM_EINSTEINGRID_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "Grid.h"

class EinsteinGrid : public Grid{

private:
    const long double GRAVITATIONAL_CONST = 6.674e-11; // [m^3⋅kg^−1⋅s^−2]
    const long double DISTANCE_UNIT = 1e6;             // [m] 1 distance unit = 10^6 m

    float unitDistance;
    std::vector<std::vector<sf::Vertex>> vertices;

public:
    EinsteinGrid(std::pair<float, float> window_size, float distance, float thickness = 1,
                 sf::Color color = sf::Color::White);

    void update(const std::vector<Body>& bodies);
    void draw(sf::RenderWindow & window);

private:
    bool areColliding(const sf::Vector2f position, const Body &body);
};


#endif //N_BODY_PROBLEM_EINSTEINGRID_H
