//
// Created by viking on 09.11.2020.
//

#ifndef N_BODY_PROBLEM_EINSTEINGRID_H
#define N_BODY_PROBLEM_EINSTEINGRID_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "../Constants.h"

class EinsteinGrid : public Grid{

private:
    float unitDistance;
    std::vector<std::vector<sf::Vertex>> vertices;
    sf::Color color;

public:
    EinsteinGrid(std::pair<float, float> window_size, float distance, sf::Color color = sf::Color::White);
    ~EinsteinGrid() = default;
    void update(const std::vector<Body>& bodies);
    void draw(sf::RenderWindow & window);

private:
    bool areColliding(const sf::Vector2f position, const Body &body);
};


#endif //N_BODY_PROBLEM_EINSTEINGRID_H
