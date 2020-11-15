//
// Created by viking on 15.10.20.
//
#include <random>
#include <sstream>
#include "../includes/Body.h"

Body::Body(double mass, float radius, sf::Vector2f position)
    : mass(mass), shape(radius), description() {

    shape.setOrigin(radius, radius);
    shape.setPosition(position);
}

Body::Body(double mass, float radius, sf::Vector2f position, sf::Color color, std::unique_ptr<Spectrum> spectrum)
        : mass(mass), shape(radius), positionSpectrum(std::move(spectrum)), description(color) {

    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    shape.setOutlineThickness(1);
    shape.setFillColor(color);
    if(positionSpectrum != nullptr){
        positionSpectrum->setColor(color);
    }
}

//Body::Body(const Body &original): mass(original.mass), shape(original.shape) {}

Body::Body(Body &&original) noexcept :
        mass(original.mass),
        shape(std::move(original.shape)),
        positionSpectrum(std::move(original.positionSpectrum)),
        description(std::move(original.description)){}

void Body::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void Body::drawSpectrum(sf::RenderWindow& window) const{
    if(positionSpectrum != nullptr){
        positionSpectrum->draw(window);
    }
}

void  Body::addForce(sf::Vector2<long double> force) {
    acceleration += force / static_cast<long double>(mass);
}

void Body::move(float time_step) {
    velocity += acceleration * static_cast<long double>(time_step);
    shape.move(static_cast<sf::Vector2f>(velocity) * time_step);

    if(positionSpectrum != nullptr) {
        positionSpectrum->addPosition(shape.getPosition());
    }
}

void Body::showDescription(sf::RenderWindow& window){
    description.update(
            getPosition(),
            velocity,
            acceleration,
            getMass(),
            window);
    description.draw(window);
}

void Body::makeDescriptionActiveOnAsideFromWindow(const sf::Vector2<unsigned int> &winSize) {
    if(!isDescriptionActive() && isAsideFromWindow(winSize)){
        setDescriptionActive(true);
    }
}

bool Body::isAsideFromWindow(const sf::Vector2<unsigned int> &winSize) {
    auto pos = shape.getPosition();
    return pos.x < 0 || pos.x > winSize.x || pos.y < 0 || pos.y > winSize.y;
}

void Body::setInitialVelocity(sf::Vector2<long double> vel) noexcept {
    velocity = vel;
}
