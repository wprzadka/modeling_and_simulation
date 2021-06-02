//
// Created by viking on 23.05.21.
//

#include <cmath>
#include "../includes/Simulation.h"
#include "../includes/solver/Solver.h"
#include "../includes/Constants.h"
#include "../includes/solver/Euler.h"

//template <int N, class SolverType>
//Simulation<N, SolverType>::Simulation(const SolverType& solver = SolverType()) : solver(solver){}

//template<int N>
//void Simulation::update(std::vector<Body>& bodies){
//
//    calculateAccelerations(bodies);
//
//    std::array<sf::Vector3f, N> acceleration;
//    std::array<sf::Vector3f, N> velocity;
//    std::array<sf::Vector3f, N> position;
//    for (int i = 0; i < N; ++i){
//        acceleration[i] = bodies[i].getAcceleration();
//        velocity[i] = bodies[i].getVelocity();
//        position[i] = bodies[i].getPosition();
//    }
//
//    velocity = Euler<N>::solve(velocity, acceleration, stepSize);
//    position = Euler<N>::solve(position, velocity, stepSize);
//
//    for(int i = 0; i < N; ++i){
//        bodies[i].setVelocity(velocity[i]);
//        bodies[i].setPosition(position[i]);
//    }
//}


void Simulation::calculateAccelerations(std::vector<Body>& bodies){
    for (auto &body : bodies) {
        body.clearAcceleration();
    }
    for (int k = 0; k < bodies.size(); ++k) {
        for (int m = k + 1; m < bodies.size(); ++m) {
            if (!areColliding(bodies[k], bodies[m])) {
                sf::Vector2<long double> force = calculateForce(bodies[k], bodies[m]);
                bodies[k].addForce(-force);
                bodies[m].addForce(force);
            }
        }
    }
}

sf::Vector2<long double> Simulation::calculateForce(const Body &first, const Body &second){
    double x_diff = first.getPosition().x - second.getPosition().x; // [distance_units] -> vector
    double y_diff = first.getPosition().y - second.getPosition().y; // [distance_units] -> vector
    double diff_sqrt = std::pow(x_diff, 2) + std::pow(y_diff, 2); // [distance_units^2]
    double norm_diff = std::sqrt(diff_sqrt); // [distance_units]

    sf::Vector2<long double> diff_vec_normalized{x_diff / norm_diff, y_diff / norm_diff}; // [-] -> vector
    long double distance_sqrt = diff_sqrt * std::pow(DISTANCE_UNIT, 2); // [m^2]
    return diff_vec_normalized * static_cast<long double>(first.getMass() * second.getMass())
           * GRAVITATIONAL_CONST / distance_sqrt; // [kg^2⋅m^3⋅kg^−1⋅s^−2⋅m^-2] = [kg⋅m⋅s^-2] -> vector
}

bool Simulation::areColliding(const Body &first, const Body &second){
    auto diff_vec = first.getPosition() - second.getPosition(); // [distance_units] -> vector
    auto distance = std::sqrt(std::pow(diff_vec.x, 2) + std::pow(diff_vec.y, 2)); // [distance_units] -> vector
    return distance < first.getRadius() + second.getRadius();
}
