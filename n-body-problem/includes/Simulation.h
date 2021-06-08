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

//    const SolverType solver;
    const float stepSize;
    std::array<sf::Vector2<long double>, N> acceleration;
    std::array<sf::Vector2<long double>, N> velocity;
    std::array<sf::Vector2<long double>, N> position;

public:
    explicit Simulation(float stepSize, std::vector<Body>& bodies);
    void update(std::vector<Body>& bodies);

private:
    void calculateAccelerations(std::vector<Body>& bodies);
    sf::Vector2<long double> calculateForce(const Body& a, const Body& b);
    bool areColliding(const Body &first, const Body &second);
};


#endif //N_BODY_PROBLEM_SIMULATION_H
