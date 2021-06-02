//
// Created by viking on 23.05.21.
//

#ifndef N_BODY_PROBLEM_SOLVER_H
#define N_BODY_PROBLEM_SOLVER_H

template <int N>
class Solver {
public:
    virtual std::array<sf::Vector2<long double>, N> solve(
            std::array<sf::Vector2<long double>, N> prevValue,
            std::array<sf::Vector2<long double>, N> derivative,
            float stepSize) = 0;

};


#endif //N_BODY_PROBLEM_SOLVER_H
