//
// Created by viking on 15.10.20.
//
#include <SFML/Graphics.hpp>
#include <cmath>
#include "includes/Body.h"

sf::Vector2<long double> calculateForce(const Body &first, const Body &second);
bool areColliding(const Body& first, const Body& second);

static const long double GRAVITATIONAL_CONST = 1; // 6.674e-11; // [m3⋅kg^−1⋅s^−2]
static const long double DISTANCE_UNIT = 1e7;             // 1 distance unit = 10^6 m

int main(int argc, char* argv[]){

    printf("gravitational constant = %Lf", GRAVITATIONAL_CONST);

    std::vector<Body> bodies{
        Body{7.347e11, 5, {750, 350}},
        Body{5.972e13, 20, {800, 450}},
        Body{5.972e13, 5, {850, 250}},
        Body{5.972e13, 5, {650, 450}},
        Body{5.972e13, 5, {600, 350}}
        // * 1e-11 instead of multiply with GRAV_CONST
    };

    sf::RenderWindow window(sf::VideoMode(1200, 900), "n-body");
    window.setFramerateLimit(60);

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
            body.move(1);
        }

        for(const auto& body : bodies){
            body.draw(window);
        }

        window.display();
    }
    return 0;
}

sf::Vector2<long double> calculateForce(const Body &first, const Body &second){
    double x_diff = first.getPosition().x - second.getPosition().x;
    double y_diff = first.getPosition().x - second.getPosition().x;
    double diff_sqrt = std::pow(x_diff, 2) + std::pow(y_diff, 2);
    double norm_diff = std::sqrt(diff_sqrt);

    sf::Vector2<long double> diff_vec{x_diff / norm_diff, y_diff / norm_diff};
    long double distance_cubed = diff_sqrt * std::pow(DISTANCE_UNIT, 2);
    return diff_vec * static_cast<long double>(first.getMass() * second.getMass()) 
        * GRAVITATIONAL_CONST / distance_cubed;
}

bool areColliding(const Body &first, const Body &second){
    auto diff_vec = first.getPosition() - second.getPosition();
    auto distance = std::sqrt(std::pow(diff_vec.x, 2) + std::pow(diff_vec.y, 2));
    return distance < first.getRadius() + second.getRadius();
}