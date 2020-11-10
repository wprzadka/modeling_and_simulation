//
// Created by viking on 15.10.20.
//
#include <random>
#include <sstream>
#include "../includes/Body.h"

Body::Body(double mass, float radius, sf::Vector2f position)
    : mass(mass), shape(radius), font(), description() {

    shape.setOrigin(radius, radius);
    shape.setPosition(position);

    if(font.loadFromFile("../font/FreeSans.otf")){
        description.setFont(font);
    }
    description.setCharacterSize(20);
}

Body::Body(double mass, float radius, sf::Vector2f position, sf::Color color, std::unique_ptr<Spectrum> spectrum)
        : mass(mass), shape(radius), positionSpectrum(std::move(spectrum)), font(), description() {

    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    shape.setOutlineThickness(1);
    shape.setFillColor(color);
    if(positionSpectrum != nullptr){
        positionSpectrum->setColor(color);
    }

    if(font.loadFromFile("../font/FreeSans.otf")){
        description.setFont(font);
    }
    description.setCharacterSize(20);
}

//Body::Body(const Body &original): mass(original.mass), shape(original.shape) {}

Body::Body(Body &&original) noexcept :
        mass(original.mass),
        shape(std::move(original.shape)),
        positionSpectrum(std::move(original.positionSpectrum)),
        font(original.font),
        description(original.description)
        {
    if(font.loadFromFile("../font/FreeSans.otf")){
        description.setFont(font);
    }
    description.setCharacterSize(20);
}

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

void Body::showDescription(sf::RenderWindow& window) {
    updateDescription();
    window.draw(description);
}

void Body::updateDescription() {
    sf::Vector2f pos = shape.getPosition();

    std::ostringstream data;
    data.precision(0);
    data << std::fixed;
    data << "position: ("
         << pos.x << ", "
        << pos.y << ")\n";
    data.precision(1);
    data << "velocity: ("
        << velocity.x << ", "
        << velocity.y << ")\n";
    data << "force: "
        << acceleration.x << ", "
        << acceleration.y << ")";
    description.setString(data.str());
    description.setPosition(pos.x, pos.y);
}
