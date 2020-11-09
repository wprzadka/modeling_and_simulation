//
// Created by viking on 09.11.2020.
//

#ifndef N_BODY_PROBLEM_SPACEGRID_H
#define N_BODY_PROBLEM_SPACEGRID_H


#include <vector>
#include <SFML/Graphics.hpp>

class SpaceGrid {

    std::vector<sf::RectangleShape> lines;

public:
    SpaceGrid(std::pair<float, float> window_size, float distance,
              float thickness = 1, sf::Color color = sf::Color::White);

    void draw(sf::RenderWindow& window);
};


#endif //N_BODY_PROBLEM_SPACEGRID_H
