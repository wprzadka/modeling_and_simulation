//
// Created by viking on 24.10.20.
//


#include "../../includes/spectrum/LinearSpectrum.h"

LinearSpectrum::LinearSpectrum(): points(sf::Lines), color(0, 0, 0) {
}

void LinearSpectrum::draw(sf::RenderWindow& window) {
    window.draw(points);
}

void LinearSpectrum::setColor(const sf::Color& newColor){
    color = newColor;
}


void LinearSpectrum::addPosition(sf::Vector2f position) {
    points.append(sf::Vertex(position, color));
}