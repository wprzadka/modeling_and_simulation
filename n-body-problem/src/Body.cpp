//
// Created by viking on 15.10.20.
//
#include <random>
#include "../includes/Body.h"
#include "../includes/LinearSpectrum.h"

/*
Body::Body(double mass, int radius)
    : mass(mass), shape(radius) {

    auto x = rand() % 1000 + 100;
    auto y = rand() % 700 + 100;
    shape.setPosition(x, y);
}
*/
Body::Body(double mass, int radius, sf::Vector2f position): mass(mass), shape(radius) {

    shape.setPosition(position);
}

Body::Body(double mass, int radius, sf::Vector2f position, std::unique_ptr<Spectrum> vidmo)
        : mass(mass), shape(radius), positionVidmo(std::move(vidmo)) {

    shape.setPosition(position);
}

Body::Body(const Body &original): mass(original.mass), shape(original.shape) {}

Body::Body(Body &&original):
    mass(original.mass),
    shape(std::move(original.shape)),
    positionVidmo(std::move(original.positionVidmo)){}


void Body::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    if(positionVidmo != nullptr){
        positionVidmo->draw(window);
    }
}

void  Body::addForce(sf::Vector2<long double> force) {
    acceleration += force / static_cast<long double>(mass);
}

void Body::move(float time_step) {
    velocity += acceleration * static_cast<long double>(time_step);
    shape.move(static_cast<sf::Vector2f>(velocity) * time_step);

    if(positionVidmo != nullptr) {
        printf("add");
        positionVidmo->addPosition(shape.getPosition());
    }
    clearAcceleration();
}
