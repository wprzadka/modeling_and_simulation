//
// Created by viking on 15.10.20.
//
#include <random>
#include "../includes/Body.h"

Body::Body(double mass, int radius)
    : mass(mass), shape(radius) {

    auto x = rand() % 1000 + 100;
    auto y = rand() % 700 + 100;
    shape.setPosition(x, y);
}

Body::Body(double mass, int radius, sf::Vector2f position)
    : mass(mass), shape(radius) {

    shape.setPosition(position);
}

void Body::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void  Body::addForce(sf::Vector2<long double> force) {
    acceleration += force / static_cast<long double>(mass);
}

void Body::move(float time_step) {
    velocity += acceleration * static_cast<long double>(time_step);
    shape.move(static_cast<sf::Vector2f>(velocity) * time_step);

    clearAcceleration();
}
