//
// Created by viking on 15.10.20.
//
#include <SFML/Graphics.hpp>
#include <cmath>
#include "includes/Body.h"
#include "includes/LinearVidmo.h"

sf::Vector2<long double> calculateForce(const Body &first, const Body &second);
bool areColliding(const Body& first, const Body& second);

static const long double GRAVITATIONAL_CONST = 6.674e-11; // [m^3⋅kg^−1⋅s^−2]
static const long double DISTANCE_UNIT = 1e6;             // [m] 1 distance unit = 10^6 m
static const int TIME_STEP = 10;                          // [s] amount of time in one iteration

int main(int argc, char* argv[]){

//    printf("gravitational constant = %Lf", GRAVITATIONAL_CONST);

    std::vector<Body> bodies{
//        Body{7.347e22, 10, {750, 350}},
//        Body{5.972e24, 40, {800, 450}},
//        Body{5.972e22, 10, {660, 250}, std::make_unique<LinearVidmo>(10)},
        Body{5.972e22, 10, {630, 450}, std::make_unique<LinearVidmo>(10)},
        Body{5.972e22, 10, {600, 350}, std::make_unique<LinearVidmo>(10)}
        // * multiply mass by 1e-11 instead of multiply later with GRAV_CONST
    };
    bodies.emplace_back(std::move(Body{5.972e22, 10, {660, 250}, std::make_unique<LinearVidmo>(10)}));

    sf::RenderWindow window(sf::VideoMode(1200, 900), "n-body");
    window.setFramerateLimit(360);

    while(window.isOpen()){


        sf::Event event{};
        if(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();

        for(int k = 0; k < bodies.size(); ++k){
            for(int m = k + 1; m < bodies.size(); ++m){

                if(!areColliding(bodies[k], bodies[m])){
                    sf::Vector2<long double> force = calculateForce(bodies[k], bodies[m]);

                    bodies[k].addForce(-force);
                    bodies[m].addForce(force);
                }
            }
        }

        for(auto& body : bodies){
            body.move(TIME_STEP);
        }

        for(const auto& body : bodies){
            body.draw(window);
        }

        window.display();
    }
    return 0;
}

sf::Vector2<long double> calculateForce(const Body &first, const Body &second){
    double x_diff = first.getPosition().x - second.getPosition().x; // [distance_units] -> vector
    double y_diff = first.getPosition().y - second.getPosition().y; // [distance_units] -> vector
    double diff_sqrt = std::pow(x_diff, 2) + std::pow(y_diff, 2); // [distance_units^2]
    double norm_diff = std::sqrt(diff_sqrt); // [distance_units]

    sf::Vector2<long double> diff_vec_normalized{x_diff / norm_diff, y_diff / norm_diff}; // [-] -> vector
    long double distance_sqrt = diff_sqrt * std::pow(DISTANCE_UNIT, 2); // [m^2]
    return diff_vec_normalized * static_cast<long double>(first.getMass() * second.getMass())
        * GRAVITATIONAL_CONST / distance_sqrt; // [kg^2⋅m^3⋅kg^−1⋅s^−2⋅m^-2] = [kg⋅m⋅s^-2] -> vector
}

bool areColliding(const Body &first, const Body &second){
    auto diff_vec = first.getPosition() - second.getPosition(); // [distance_units] -> vector
    auto distance = std::sqrt(std::pow(diff_vec.x, 2) + std::pow(diff_vec.y, 2)); // [distance_units] -> vector
    return distance < first.getRadius() + second.getRadius();
}
