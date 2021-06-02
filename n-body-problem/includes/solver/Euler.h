//
// Created by viking on 15.05.21.
//
#ifndef N_BODY_PROBLEM_EULER_H
#define N_BODY_PROBLEM_EULER_H


#include <SFML/Window.hpp>
#include "Solver.h"

class Euler {
public:
    template <int N>
    static std::array<sf::Vector2<long double>, N> solve(
            std::array<sf::Vector2<long double>, N> prevValue,
            std::array<sf::Vector2<long double>, N> derivative,
            long double stepSize){

        std::array<sf::Vector2<long double>, N> nextValue;
        for (int i = 0; i < N; ++i){
            nextValue[i] = prevValue[i] + stepSize * derivative[i];
        }
        return nextValue;
    }
};


#endif //N_BODY_PROBLEM_EULER_H
