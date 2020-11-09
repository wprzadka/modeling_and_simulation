//
// Created by viking on 09.11.2020.
//

#ifndef N_BODY_PROBLEM_MASSCENTER_H
#define N_BODY_PROBLEM_MASSCENTER_H

#include <SFML/Graphics.hpp>
#include "Body.h"

class MassCenter {

    sf::Vector2<double> massCenterPosition{0, 0};
    long double totalMassOfSystem = 0;
    sf::CircleShape shape;

public:
    MassCenter(float size = 1);
    MassCenter(const std::vector<Body>&, float size = 1);
    long double calculateTotalMass(const std::vector<Body>&);
    sf::Vector2<double> findMassCenter(const std::vector<Body>&);
    void draw(sf::RenderWindow&) const;
};


#endif //N_BODY_PROBLEM_MASSCENTER_H
