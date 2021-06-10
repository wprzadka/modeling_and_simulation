//
// Created by viking on 23.05.21.
//

#ifndef N_BODY_PROBLEM_SIMULATION_H
#define N_BODY_PROBLEM_SIMULATION_H


#include <SFML/Window.hpp>
#include "Body.h"
#include "solver/Euler.h"
#include "Constants.h"

template <unsigned int N, class SOLVER>
class Simulation {

    std::array<long double, N> mass;
    std::array<float, N> radius;

    std::array<sf::Vector2<long double>, N> velocity;
    std::array<sf::Vector2<long double>, N> position;
    const float stepSize;

public:
    explicit Simulation(float stepSize, std::vector<Body>& bodies);
    void update(std::vector<Body>& bodies);

    std::pair<
    std::array<sf::Vector2<long double>, N>,
    std::array<sf::Vector2<long double>, N>
    > computeDerivatives(
            std::array<sf::Vector2<long double>, N> pos,
            std::array<sf::Vector2<long double>, N> vel
            );

private:
    sf::Vector2<long double> calculateForce(
            const sf::Vector2<long double>& fstPos,
            const sf::Vector2<long double>& sndPos,
            const long double& fstMass,
            const long double& sndMass
            );
    bool areColliding(
            const sf::Vector2<long double>& fstPos,
            const sf::Vector2<long double>& sndPos,
            const float& fstRad,
            const float& sndRad
            );
};


#endif //N_BODY_PROBLEM_SIMULATION_H
