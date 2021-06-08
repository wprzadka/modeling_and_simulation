//
// Created by viking on 23.05.21.
//

#include <cmath>
#include "../includes/Simulation.h"
#include "../includes/Constants.h"
#include "../includes/solver/Euler.h"
#include "../src/solver/Euler.cpp"


template <unsigned int N, class SOLVER>
Simulation<N, SOLVER>::Simulation(float stepSize, std::vector<Body>& bodies): stepSize(stepSize) {
    for (int i = 0; i < N; ++i){
        position[i] = (sf::Vector2<long double>)bodies[i].getPosition(); // [unit / s^2]
    }
}

template <unsigned int N, class SOLVER>
void Simulation<N, SOLVER>::update(std::vector<Body>& bodies){

    calculateAccelerations(bodies);

    velocity = SOLVER::solve(velocity, acceleration, stepSize);
    position = SOLVER::solve(position, velocity, stepSize);
    for(int i = 0; i < N; ++i){
        bodies[i].setVelocity(velocity[i]); // [m / s]
        bodies[i].setPosition(position[i]); // [m]
    }
}

template <unsigned int N, class SOLVER>
void Simulation<N, SOLVER>::calculateAccelerations(std::vector<Body>& bodies){
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
    for (int i = 0; i < N; ++i){
        acceleration[i] = bodies[i].getAcceleration() / DISTANCE_UNIT; // [unit / s^2]
    }
}

template <unsigned int N, class SOLVER>
sf::Vector2<long double> Simulation<N, SOLVER>::calculateForce(const Body &first, const Body &second){
    double x_diff = first.getPosition().x - second.getPosition().x; // [distance_units] -> vector
    double y_diff = first.getPosition().y - second.getPosition().y; // [distance_units] -> vector
    double diff_sqrt = std::pow(x_diff, 2) + std::pow(y_diff, 2); // [distance_units^2]
    double norm_diff = std::sqrt(diff_sqrt); // [distance_units]

    sf::Vector2<long double> diff_vec_normalized{x_diff / norm_diff, y_diff / norm_diff}; // [-] -> vector
    long double distance_sqrt = diff_sqrt * std::pow(DISTANCE_UNIT, 2); // [m^2]
    return diff_vec_normalized * static_cast<long double>(first.getMass() * second.getMass())
           * GRAVITATIONAL_CONST / distance_sqrt; // [kg^2⋅m^3⋅kg^−1⋅s^−2⋅m^-2] = [kg⋅m⋅s^-2] -> vector
}

template <unsigned int N, class SOLVER>
bool Simulation<N, SOLVER>::areColliding(const Body &first, const Body &second){
    auto diff_vec = first.getPosition() - second.getPosition(); // [distance_units] -> vector
    auto distance = std::sqrt(std::pow(diff_vec.x, 2) + std::pow(diff_vec.y, 2)); // [distance_units] -> vector
    return distance < first.getRadius() + second.getRadius();
}
