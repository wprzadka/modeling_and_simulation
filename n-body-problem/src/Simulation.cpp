//
// Created by viking on 23.05.21.
//

#include <cmath>
#include <zconf.h>
#include "../includes/Simulation.h"
#include "../includes/Constants.h"
#include "../includes/solver/Euler.h"
#include "../includes/solver/RungeKutta.h"
#include "../includes/solver/Trapezoidal.h"


template <unsigned int N, class SOLVER>
Simulation<N, SOLVER>::Simulation(float stepSize, std::vector<Body>& bodies): stepSize(stepSize) {
    for (int i = 0; i < N; ++i){
        mass[i] = bodies[i].getMass();
        radius[i] = bodies[i].getRadius();
        position[i] = (sf::Vector2<long double>)bodies[i].getPosition(); // [unit / s^2]
    }
    std::fill(velocity.begin(), velocity.end(), sf::Vector2<long double>{0,0});
}

template <unsigned int N, class SOLVER>
void Simulation<N, SOLVER>::update(std::vector<Body>& bodies){

    auto next = Trapezoidal::solve<N>(
            time,
            position,
            velocity,
            [&](
                    float time,
                    std::array<sf::Vector2<long double>, N> pos,
                    std::array<sf::Vector2<long double>, N> vel
            ){
                return computeDerivatives(time, pos, vel);
            },
            stepSize
            );
    position = next.first;
    velocity = next.second;

    for(int i = 0; i < N; ++i){
        bodies[i].setPosition(position[i]); // [m]
    }
}

template<unsigned int N, class SOLVER>
std::pair<
std::array<sf::Vector2<long double>, N>,
std::array<sf::Vector2<long double>, N>
> Simulation<N, SOLVER>::computeDerivatives(
        float time,
        std::array<sf::Vector2<long double>, N> pos,
        std::array<sf::Vector2<long double>, N> vel
        ) {

    std::array<sf::Vector2<long double>, N> acc{};
    std::fill(acc.begin(), acc.end(), sf::Vector2<long double>{0, 0});

    for (int k = 0; k < N; ++k) {
        for (int m = k + 1; m < N; ++m) {
            if (!areColliding(pos[k], pos[m], radius[k], radius[m])) {
                sf::Vector2<long double> pair_force = calculateForce(pos[k], pos[m], mass[k], mass[m]);
                acc[k] -= pair_force / mass[k] / DISTANCE_UNIT; // [unit / s^2]
                acc[m] += pair_force / mass[m] / DISTANCE_UNIT; // [unit / s^2]
            }
        }
    }
    return std::make_pair(vel, acc);
}

template <unsigned int N, class SOLVER>
sf::Vector2<long double> Simulation<N, SOLVER>::calculateForce (
        const sf::Vector2<long double>& fstPos,
        const sf::Vector2<long double>& sndPos,
        const long double& fstMass,
        const long double& sndMass
        ){
    sf::Vector2<long double> diff = fstPos - sndPos; // [distance_units] -> vector
    long double diff_sqrt = std::pow(diff.x, 2) + std::pow(diff.y, 2); // [distance_units^2]
    long double norm_diff = std::sqrt(diff_sqrt); // [distance_units]

    sf::Vector2<long double> diff_vec_normalized{diff.x / norm_diff, diff.y / norm_diff}; // [-] -> vector
    long double distance_sqrt = diff_sqrt * std::pow(DISTANCE_UNIT, 2); // [m^2]
    return diff_vec_normalized * static_cast<long double>(fstMass * sndMass)
           * GRAVITATIONAL_CONST / distance_sqrt; // [kg^2⋅m^3⋅kg^−1⋅s^−2⋅m^-2] = [kg⋅m⋅s^-2] -> vector
}

template <unsigned int N, class SOLVER>
bool Simulation<N, SOLVER>::areColliding(
        const sf::Vector2<long double>& fstPos,
        const sf::Vector2<long double>& sndPos,
        const float& fstRad,
        const float& sndRad
        ){
    auto diff_vec = fstPos - sndPos; // [distance_units] -> vector
    auto distance = std::sqrt(std::pow(diff_vec.x, 2) + std::pow(diff_vec.y, 2)); // [distance_units] -> vector
    return distance < fstRad + sndRad;
}
