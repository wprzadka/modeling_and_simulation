//
// Created by viking on 23.05.21.
//

#ifndef N_BODY_PROBLEM_SIMULATION_H
#define N_BODY_PROBLEM_SIMULATION_H


#include <SFML/Window.hpp>
#include "Body.h"
#include "solver/Euler.h"
#include "Constants.h"

class Simulation {

//    const SolverType solver;
    const float stepSize;

public:
    explicit Simulation(float stepSize);

//    Simulation(const SolverType& solver);
    template <int N>
//    void update(std::vector<Body>& bodies);
    void update(std::vector<Body>& bodies){

        calculateAccelerations(bodies);

//        for (auto& body : bodies){
//            body.move(stepSize);
//        }


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
            bodies[i].setPosition(position[i]);
        }

    }

private:

    void calculateAccelerations(std::vector<Body>& bodies);
    sf::Vector2<long double> calculateForce(const Body& a, const Body& b);
    bool areColliding(const Body &first, const Body &second);
};


#endif //N_BODY_PROBLEM_SIMULATION_H
