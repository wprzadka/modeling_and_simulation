//
// Created by viking on 24.10.20.
//


#include "../../includes/spectrum/InfinitySpectrum.h"

InfinitySpectrum::InfinitySpectrum(): points(sf::Lines), color(0, 0, 0) {
}

void InfinitySpectrum::draw(sf::RenderWindow& window) {
    window.draw(points);
}

void InfinitySpectrum::setColor(const sf::Color& newColor){
    color = newColor;
}


void InfinitySpectrum::addPosition(sf::Vector2f position) {
    points.append(sf::Vertex(position, color));
}