//
// Created by viking on 15.10.20.
//
#include <SFML/Graphics.hpp>
#include <cmath>
#include "includes/Body.h"
#include "includes/spectrum/InfinitySpectrum.h"
#include "includes/MassCenter.h"
#include "includes/grid/Grid.h"
#include "includes/grid/MetricGrid.h"
#include "includes/grid/EinsteinGrid.h"
#include "includes/grid/VectorsGrid.h"
#include "includes/Constants.h"
#include "includes/spectrum/ListSpectrum.h"

static sf::Vector2<long double> calculateForce(const Body &first, const Body &second);
static bool areColliding(const Body& first, const Body& second);

static const int TIME_STEP = 1;                          // [s] amount of time in one iteration

int main(){

    const std::pair<float, float> window_size{1200, 900};

    std::vector<Body> bodies{};
    bodies.emplace_back(std::move(Body{5.972e24, 10,{630, 450},
                                       sf::Color(255, 100, 100),
                                       std::make_unique<ListSpectrum>()}));
    bodies.emplace_back(std::move(Body{5.972e24, 10, {600, 350},
                                       sf::Color(100, 255, 100),
                                       std::make_unique<ListSpectrum>()}));
    bodies.emplace_back(std::move(Body{5.972e24, 10, {660, 250},
                                       sf::Color(100, 100, 255),
                                       std::make_unique<ListSpectrum>()}));

    sf::RenderWindow window(sf::VideoMode(window_size.first, window_size.second), "n-body");
    window.setFramerateLimit(60);

    MassCenter center{bodies, 2};
    std::unique_ptr<Grid> grid = std::make_unique<VectorsGrid>(window_size, 20,
                                                              sf::Color(60, 60, 60));

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
        grid->update(bodies);
        grid->draw(window);
        for(const auto& body : bodies){
            body.drawSpectrum(window);
        }
        for(const auto& body : bodies){
            body.draw(window);
        }
        center.draw(window);
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
