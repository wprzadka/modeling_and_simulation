//
// Created by viking on 15.10.20.
//

#ifndef N_BODY_PROBLEM_BODY_H
#define N_BODY_PROBLEM_BODY_H


#include <SFML/Graphics.hpp>
#include "spectrum/Spectrum.h"
#include "Description.h"

class Body {
    double mass;
    sf::Vector2<long double> velocity{0, 0};
    sf::Vector2<long double> acceleration{0, 0};
    sf::CircleShape shape;
    std::unique_ptr<Spectrum> positionSpectrum = nullptr;
    Description description;

public:
//    Body(double mass, int radius);
    Body(double mass, float radius, sf::Vector2f position);
    Body(double mass, float radius, sf::Vector2f position, sf::Color color,
         std::unique_ptr<Spectrum> spectrum = nullptr);
//    Body(const Body& original);
    Body(Body&& original) noexcept;
    virtual ~Body() = default;

    void draw(sf::RenderWindow&) const;
    void drawSpectrum(sf::RenderWindow&) const;
    void addForce(sf::Vector2<long double> force);
    void move(float time_step);
    void setPosition(const sf::Vector2<long double>& position);
    void setVelocity(sf::Vector2<long double> vel) noexcept;

    void clearAcceleration() noexcept { acceleration = {0, 0}; }
    double getMass() const noexcept { return mass; };
    sf::Vector2<long double> getAcceleration() const noexcept { return acceleration; };
    sf::Vector2<long double> getVelocity() const noexcept { return velocity; };
    sf::Vector2f getPosition() const noexcept { return shape.getPosition(); };
    float getRadius() const noexcept { return shape.getRadius(); };

    void showDescription(sf::RenderWindow& window);
    bool isDescriptionActive() const noexcept { return description.isActive; };
    void setDescriptionActive(bool active){ description.isActive = active; };
    void makeDescriptionActiveOnAsideFromWindow(const sf::Vector2<unsigned int> &winSize);
    bool isAsideFromWindow(const sf::Vector2<unsigned int> &winSize);
};


#endif //N_BODY_PROBLEM_BODY_H
