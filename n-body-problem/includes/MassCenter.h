//
// Created by viking on 09.11.2020.
//

#ifndef N_BODY_PROBLEM_MASSCENTER_H
#define N_BODY_PROBLEM_MASSCENTER_H

#include <SFML/Graphics.hpp>
#include <deque>
#include "Body.h"

class MassCenter {

    sf::Vector2<double> massCenterPosition{0, 0};
    long double totalMassOfSystem = 0;
    sf::CircleShape shape;

    sf::Vector2<double> initialMassCenterPosition{0, 0};
    std::deque<double> displacement{0, 0};

public:
    MassCenter(float size = 1);
    MassCenter(const std::vector<Body>&, float size = 1);
    long double calculateTotalMass(const std::vector<Body>&);
    sf::Vector2<double> getMassCenter(const std::vector<Body>&);
    sf::Vector2<double> saveInitialMassCenter(const std::vector<Body>&);
    std::deque<double> getDisplacement(){ return displacement; };
    void draw(sf::RenderWindow&) const;

private:
    sf::Vector2<double> findMassCenter(const std::vector<Body>&);

};


#endif //N_BODY_PROBLEM_MASSCENTER_H
