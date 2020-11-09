//
// Created by viking on 09.11.2020.
//

#ifndef N_BODY_PROBLEM_METRICGRID_H
#define N_BODY_PROBLEM_METRICGRID_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "Body.h"

class MetricGrid {

    std::vector<sf::RectangleShape> lines;

public:
    MetricGrid(std::pair<float, float> window_size, float distance,
               float thickness = 1, sf::Color color = sf::Color::White);
    void update(const std::vector<Body>&){};
    void draw(sf::RenderWindow& window);
};


#endif //N_BODY_PROBLEM_METRICGRID_H
