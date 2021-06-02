//
// Created by viking on 23.05.21.
//

#ifndef N_BODY_PROBLEM_SIMULATION_H
#define N_BODY_PROBLEM_SIMULATION_H


#include <SFML/Window.hpp>
#include "Body.h"
#include "solver/Euler.h"

class Simulation {

//    const SolverType solver;
    const long double stepSize = 0.1;

public:

//    Simulation(const SolverType& solver);
    template <int N>
//    void update(std::vector<Body>& bodies);
    void update(std::vector<Body>& bodies){

        calculateAccelerations(bodies);

        std::array<sf::Vector2<long double>, N> acceleration;
        std::array<sf::Vector2<long double>, N> velocity;
        std::array<sf::Vector2<long double>, N> position;
        for (int i = 0; i < N; ++i){
            acceleration[i] = bodies[i].getAcceleration();
            velocity[i] = bodies[i].getVelocity();
            position[i] = (sf::Vector2<long double>)bodies[i].getPosition();
        }

        velocity = Euler::solve<N>(velocity, acceleration, stepSize);
        position = Euler::solve<N>(position, velocity, stepSize);

        for(int i = 0; i < N; ++i){
            bodies[i].setVelocity(velocity[i]);
            float pos_x = position[i].x;
            float pos_y = position[i].y;
            bodies[i].setPosition(sf::Vector2f(pos_x, pos_y));
        }
    }

private:

    void calculateAccelerations(std::vector<Body>& bodies);
    sf::Vector2<long double> calculateForce(const Body& a, const Body& b);
    bool areColliding(const Body &first, const Body &second);
};


#endif //N_BODY_PROBLEM_SIMULATION_H
