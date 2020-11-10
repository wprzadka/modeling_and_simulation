//
// Created by viking on 24.10.20.
//


#include "../../includes/spectrum/InfinitySpectrum.h"

InfinitySpectrum::InfinitySpectrum(): Spectrum(), points(sf::LinesStrip) {
}

void InfinitySpectrum::draw(sf::RenderWindow& window) {
    window.draw(points);
}

void InfinitySpectrum::addPosition(sf::Vector2f position) {
    points.append(sf::Vertex(position, color));
}
