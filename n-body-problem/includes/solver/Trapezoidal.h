//
// Created by viking on 15.05.21.
//
#ifndef N_BODY_PROBLEM_TRAPEZOIDAL_H
#define N_BODY_PROBLEM_TRAPEZOIDAL_H

#include "RungeKutta.h"
#include <functional>

class Trapezoidal {
public:

    template <unsigned long int N>
    static std::pair<
            std::array<sf::Vector2<long double>, N>,
            std::array<sf::Vector2<long double>, N>
    > solve(
            std::array<sf::Vector2<long double>, N> pos,
            std::array<sf::Vector2<long double>, N> vel,
            std::function<
                    std::pair<
                            std::array<sf::Vector2<long double>, N>,
                            std::array<sf::Vector2<long double>, N>
                    >(
                            std::array<sf::Vector2<long double>, N>,
                            std::array<sf::Vector2<long double>, N>
                    )> f,
            long double stepSize
    ){

        std::array<sf::Vector2<long double>, N> nextPos{};
        std::array<sf::Vector2<long double>, N> nextVel{};

        std::pair<
                std::array<sf::Vector2<long double>, N>,
                std::array<sf::Vector2<long double>, N>
        > rk4 = RungeKutta::solve<N>(pos, vel, f, stepSize);

        std::pair<
            std::array<sf::Vector2<long double>, N>,
            std::array<sf::Vector2<long double>, N>
        > derivative = f(pos, vel);

        std::array<sf::Vector2<long double>, N> estimatedPos{};
        std::array<sf::Vector2<long double>, N> estimatedVel{};
        for(int i = 0; i < N; ++i){
            estimatedPos[i] = pos[i] + rk4.first[i];
            estimatedVel[i] = vel[i] + rk4.second[i];
        }

        std::pair<
            std::array<sf::Vector2<long double>, N>,
            std::array<sf::Vector2<long double>, N>
        > nextDerivative = f(estimatedPos, estimatedVel);

        for (int i = 0; i < N; ++i){
            nextPos[i] = pos[i] + stepSize * 0.5l * (derivative.first[i] + nextDerivative.first[i]);
            nextVel[i] = vel[i] + stepSize * 0.5l * (derivative.second[i] + nextDerivative.second[i]);
        }
        return std::make_pair(nextPos, nextVel);
    }

};


#endif //N_BODY_PROBLEM_TRAPEZOIDAL_H
