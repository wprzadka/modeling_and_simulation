//
// Created by viking on 15.05.21.
//
#ifndef N_BODY_PROBLEM_EULER_H
#define N_BODY_PROBLEM_EULER_H

#include <functional>

template <unsigned long int N>
class Euler {
public:

    static std::pair<
            std::array<sf::Vector2<long double>, N>,
            std::array<sf::Vector2<long double>, N>
    > solve(
            const std::array<sf::Vector2<long double>, N>& pos,
            const std::array<sf::Vector2<long double>, N>& vel,
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
        > derivative = f(pos, vel);
        for (int i = 0; i < N; ++i){
            nextPos[i] = pos[i] + stepSize * derivative.first[i];
            nextVel[i] = vel[i] + stepSize * derivative.second[i];
        }
        return std::make_pair(nextPos, nextVel);
    }

};


#endif //N_BODY_PROBLEM_EULER_H
