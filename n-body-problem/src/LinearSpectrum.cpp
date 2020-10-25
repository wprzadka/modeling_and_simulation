//
// Created by viking on 24.10.20.
//


#include "../includes/LinearSpectrum.h"

LinearSpectrum::LinearSpectrum(int numOfPoints): points(sf::Lines, numOfPoints) {}

void LinearSpectrum::draw(const sf::RenderWindow& window) {
//    window.draw(points, sf::RenderStates());
    printf("draw\n");
}

void LinearSpectrum::addPosition(sf::Vector2f possition) {
    points.append(sf::Vertex(possition));
}