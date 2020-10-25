//
// Created by viking on 15.10.20.
//

#ifndef N_BODY_PROBLEM_BODY_H
#define N_BODY_PROBLEM_BODY_H


#include <SFML/Graphics.hpp>
#include "Spectrum.h"

class Body {
    double mass;
    sf::Vector2<long double> velocity{0, 0};
    sf::Vector2<long double> acceleration{0, 0};
    sf::CircleShape shape;
    std::unique_ptr<Spectrum> positionSpectrum = nullptr;

public:
//    Body(double mass, int radius);
    Body(double mass, float radius, sf::Vector2f position);
    Body(double mass, float radius, sf::Vector2f position, sf::Color color,
         std::unique_ptr<Spectrum> spectrum = nullptr);
    Body(const Body& original);
    Body(Body&& original) noexcept;
    virtual ~Body() = default;

    void draw(sf::RenderWindow&) const;
    void addForce(sf::Vector2<long double> force);
    void move(float time_step);

    void clearAcceleration() noexcept { acceleration = {0, 0}; }
    double getMass() const noexcept { return mass; };
    sf::Vector2f getPosition() const noexcept { return shape.getPosition(); };
    float getRadius() const noexcept { return shape.getRadius(); };
};


#endif //N_BODY_PROBLEM_BODY_H
