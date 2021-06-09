//
// Created by viking on 15.05.21.
//
#ifndef N_BODY_PROBLEM_RUNGE_KUTTA_H
#define N_BODY_PROBLEM_RUNGE_KUTTA_H


class RungeKutta {
public:
    template <unsigned long int N>
    static std::pair<
    std::array<sf::Vector2<long double>, N>,
    std::array<sf::Vector2<long double>, N>
    > solve(
            float time,
            std::array<sf::Vector2<long double>, N> pos,
            std::array<sf::Vector2<long double>, N> vel,
            std::function<
            std::pair<
                    std::array<sf::Vector2<long double>, N>,
            std::array<sf::Vector2<long double>, N>
    >(
    float,
    std::array<sf::Vector2<long double>, N>,
    std::array<sf::Vector2<long double>, N>
    )> f,
    long double stepSize
    ){
        std::array<sf::Vector2<long double>, N> nextPos{};
        std::array<sf::Vector2<long double>, N> nextVel{};

//        k1
        auto k1 = f(time, pos, vel);

        std::array<sf::Vector2<long double>, N> tempPos{};
        std::array<sf::Vector2<long double>, N> tempVel{};
//        k2
        for (int i = 0; i < N; ++i) {
            tempPos[i] = pos[i] + k1.first[i] / 2.0l;
            tempVel[i] = vel[i] + k1.second[i] / 2.0l;
        }
        auto k2 = f(time + stepSize / 2, tempPos, tempVel);
//        k3
        for (int i = 0; i < N; ++i) {
            tempPos[i] = pos[i] + k2.first[i] / 2.0l;
            tempVel[i] = vel[i] + k2.second[i] / 2.0l;
        }
        auto k3 = f(time + stepSize / 2, tempPos, tempVel);

        for (int i = 0; i < N; ++i) {
            tempPos[i] = pos[i] + k3.first[i];
            tempVel[i] = vel[i] + k3.second[i];
        }
        auto k4 = f(time + stepSize, tempPos, tempVel);

        for (int i = 0; i < N; ++i){

            nextPos[i] = pos[i] + stepSize * (k1.first[i] + 2.0l * k2.first[i] + 2.0l * k3.first[i] + k4.first[i]) / 6.0l;
            nextVel[i] = vel[i] + stepSize * (k1.second[i] + 2.0l * k2.second[i] + 2.0l * k3.second[i] + k4.second[i]) / 6.0l;
        }


        return std::make_pair(nextPos, nextVel);
    }

};


#endif //N_BODY_PROBLEM_RUNGE_KUTTA_H
