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
static bool isMouseCursorOn(const Body& target, const sf::RenderWindow& window, float aproxDistance = 1);

static const float TIME_STEP = 1;                          // [s] amount of time in one iteration
static float totalTime = 0;

int main(){

    const std::pair<float, float> window_size{1200, 900};

    std::vector<Body> bodies{};

//  Earth - Moon system
    bodies.emplace_back(std::move(Body{5.972e24, 10,{600, 450},
                                       sf::Color(255, 100, 100),
                                       std::make_unique<ListSpectrum>()})); // Earth
    bodies.emplace_back(std::move(Body{7.34767309e22, 2, {600 + 384.4, 450},
                                       sf::Color(100, 255, 100),
                                       std::make_unique<InfinitySpectrum>()})); // Moon
    bodies[1].setInitialVelocity(sf::Vector2<long double>{0, 1.022e3});

//  Three bodies
    /*
    bodies.emplace_back(std::move(Body{5.972e24, 10,{600, 400},
                                       sf::Color(255, 100, 100),
                                       std::make_unique<ListSpectrum>()})); // Earth
    bodies.emplace_back(std::move(Body{7.34767309e24, 10, {650, 450},
                                       sf::Color(100, 255, 100),
                                       std::make_unique<ListSpectrum>()})); // Moon
    bodies.emplace_back(std::move(Body{5.972e24, 10, {550, 500},
                                       sf::Color(100, 100, 255),
                                       std::make_unique<ListSpectrum>()}));
    */
    sf::RenderWindow window(sf::VideoMode(window_size.first, window_size.second), "n-body");
    window.setFramerateLimit(60);

    MassCenter center{bodies, 2};
    std::unique_ptr<Grid> grid = std::make_unique<MetricGrid>(window_size, 20,
                                                              sf::Color(60, 60, 60));

    bool isSimulationRunning = true;
    bool isDrawingEverytime;
    int drawingInterval = 4096;

    while(window.isOpen()){
        sf::Event event{};
        if(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        for(auto& body : bodies){
                            if(isMouseCursorOn(body, window, 20)){
                                body.setDescriptionActive(!body.isDescriptionActive());
                            }
                        }
                    }
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::P){
                        printf("Pause\n");
                        printf("total time: %f\n", totalTime);
                        isSimulationRunning = !isSimulationRunning;
                    }
            }
        }
        if(isSimulationRunning) {
            totalTime += TIME_STEP;

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
            for (auto &body : bodies) {
                body.move(TIME_STEP);
            }
            grid->update(bodies);

            isDrawingEverytime = false;
        }else{
            isDrawingEverytime = true;
        }

        if(isDrawingEverytime || static_cast<int>(totalTime) % drawingInterval == 0) {
            window.clear();
            grid->draw(window);

            for (const auto &body : bodies) {
                body.drawSpectrum(window);
            }
            for (const auto &body : bodies) {
                body.draw(window);
            }
            for (auto &body : bodies) {
                if (body.isDescriptionActive() || isMouseCursorOn(body, window, 20)) {
                    body.showDescription(window);
                } else {
                    body.makeDescriptionActiveOnAsideFromWindow(window.getSize());
                }
            }
            center.draw(window);
            window.display();
        }
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

bool isMouseCursorOn(const Body& target, const sf::RenderWindow& window, float aproxDistance){
    auto diff_vec = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - target.getPosition(); // [distance_units] -> vector
    auto distance = std::sqrt(std::pow(diff_vec.x, 2) + std::pow(diff_vec.y, 2)); // [distance_units] -> vector
    return distance < target.getRadius() + aproxDistance;
}