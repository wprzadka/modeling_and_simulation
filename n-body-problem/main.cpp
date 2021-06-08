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
#include "includes/Simulation.h"
#include "src/Simulation.cpp"
#include "includes/solver/Euler.h"

static bool isMouseCursorOn(const Body& target, const sf::RenderWindow& window, float aproxDistance = 1);

static const float TIME_STEP = 1;                          // [s] amount of time in one iteration
static float totalTime = 0;

int main(){

    const std::pair<float, float> window_size{1200, 900};
//    const std::pair<float, float> window_size{1920, 1080};

    std::vector<Body> bodies{};

    //  Sun - Earth system
    // DISTANCE_UNIT = 1e9 [m]
    /*
    bodies.emplace_back(std::move(Body{1.989e30, 20,{600, 450},
                                       sf::Color(255, 100, 100),
                                       std::make_unique<ListSpectrum>()})); // Sun
    bodies.emplace_back(std::move(Body{5.972e24, 2, {600 + 149.6, 450},
                                       sf::Color(100, 255, 100),
                                       std::make_unique<InfinitySpectrum>()})); // Earth
    bodies[1].setVelocity(sf::Vector2<long double>{0, 2.97705782442e4});
    */
    //  Earth - Moon system
    // DISTANCE_UNIT = 1e6 [m]
    /*
    bodies.emplace_back(std::move(Body{5.972e24, 10,{600, 450},
                                       sf::Color(100, 255, 100),
                                       std::make_unique<ListSpectrum>()})); // Earth
    bodies.emplace_back(std::move(Body{7.34767309e22, 2, {600 + 384.4, 450},
                                       sf::Color(100, 100, 255),
                                       std::make_unique<InfinitySpectrum>()})); // Moon
    bodies[1].setVelocity(sf::Vector2<long double>{0, 1.022e3});
    */
    //  Three bodies
    // DISTANCE_UNIT = 1e6 [m]
    /*
    bodies.emplace_back(std::move(Body{5.972e24, 5,{600, 400},
                                       sf::Color(255, 100, 100),
                                       std::make_unique<ListSpectrum>()}));
    bodies.emplace_back(std::move(Body{7.34767309e24, 5, {650, 450},
                                       sf::Color(100, 255, 100),
                                       std::make_unique<ListSpectrum>()}));
    bodies.emplace_back(std::move(Body{5.972e24, 5, {550, 500},
                                       sf::Color(100, 100, 255),
                                       std::make_unique<ListSpectrum>()}));
    */
    //  Five bodies
    // DISTANCE_UNIT = 1e6 [m]

    bodies.emplace_back(std::move(Body{5.972e24, 5, {400, 650},
                                       sf::Color(100, 150, 150),
                                       std::make_unique<ListSpectrum>()}));
    bodies.emplace_back(std::move(Body{7.34767309e24, 5, {400, 450},
                                       sf::Color(150, 150, 100),
                                       std::make_unique<ListSpectrum>()}));
    bodies.emplace_back(std::move(Body{5.972e24, 5, {500, 300},
                                       sf::Color(100, 100, 255),
                                       std::make_unique<ListSpectrum>()}));
    bodies.emplace_back(std::move(Body{5.972e24, 5,{550, 500},
                                       sf::Color(255, 100, 100),
                                       std::make_unique<ListSpectrum>()}));
    bodies.emplace_back(std::move(Body{7.34767309e24, 5, {600, 450},
                                       sf::Color(100, 255, 100),
                                       std::make_unique<ListSpectrum>()}));



//    for(auto& body : bodies){
//        body.setVelocity(sf::Vector2<long double>{1e3, 0});
//    }


    //  Solar system
    // DISTANCE_UNIT = 1e9 [m]
/*
    bodies.emplace_back(std::move(Body{1.989e30, 28,{600, 450},
                                       sf::Color(255, 200, 100),
                                       std::make_unique<ListSpectrum>()})); // Sun

    bodies.emplace_back(std::move(Body{3.285e23, 2, {600 + 57.91, 450},
                                       sf::Color(120, 155, 100),
                                       std::make_unique<InfinitySpectrum>()})); // Mercury

    bodies.emplace_back(std::move(Body{4.867e24, 8, {600 + 108.2, 450},
                                       sf::Color(250, 220, 200),
                                       std::make_unique<InfinitySpectrum>()})); // Venus

    bodies.emplace_back(std::move(Body{5.972e24, 6, {600 + 149.6, 450},
                                       sf::Color(120, 250, 150),
                                       std::make_unique<InfinitySpectrum>()})); // Earth

    bodies.emplace_back(std::move(Body{6.39e23, 4, {600 + 227.94, 450},
                                       sf::Color(255, 80, 50),
                                       std::make_unique<InfinitySpectrum>()})); // Mars

    bodies.emplace_back(std::move(Body{1.898e27, 14, {600 + 778.5, 450},
                                       sf::Color(255, 220, 140),
                                       std::make_unique<InfinitySpectrum>()})); // Jupiter

    bodies[1].setVelocity(sf::Vector2<long double>{0, 4.8e4});
    bodies[2].setVelocity(sf::Vector2<long double>{0, 3.5e4});
    bodies[3].setVelocity(sf::Vector2<long double>{0, 2.97705782442e4});
    bodies[4].setVelocity(sf::Vector2<long double>{0, 2.413e4});
    bodies[5].setVelocity(sf::Vector2<long double>{0, 1.306e4});
*/


    sf::RenderWindow window(
            sf::VideoMode(static_cast<int>(window_size.first), static_cast<int>(window_size.second)),
            "n-body");
    window.setFramerateLimit(60);

    Simulation<5, Euler> simulation(TIME_STEP, bodies);
    MassCenter center{bodies, 2};
    std::unique_ptr<Grid> grid = std::make_unique<MetricGrid>(window_size, 20, sf::Color(60, 60, 60));

    bool isSimulationRunning = true;
    bool isDrawingEverytime;

//    int drawingInterval = 1;
    int drawingInterval = 256;
//    int drawingInterval = 4096;
//    int drawingInterval = 16384;
//    int drawingInterval = 32768;

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
                        printf("total time: %f\n", totalTime);
                        isSimulationRunning = !isSimulationRunning;
                        if(!isSimulationRunning)
                            printf("Pause\n");
                    }
            }
        }
        if(isSimulationRunning) {
            totalTime += TIME_STEP;

            simulation.update(bodies);

            isDrawingEverytime = false;
        }else{
            isDrawingEverytime = true;
        }

        if(isDrawingEverytime || static_cast<int>(totalTime) % drawingInterval == 0) {

            grid->update(bodies);
            center.findMassCenter(bodies);

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

bool isMouseCursorOn(const Body& target, const sf::RenderWindow& window, float aproxDistance){
    auto diff_vec = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - target.getPosition(); // [distance_units] -> vector
    auto distance = std::sqrt(std::pow(diff_vec.x, 2) + std::pow(diff_vec.y, 2)); // [distance_units] -> vector
    return distance < target.getRadius() + aproxDistance;
}