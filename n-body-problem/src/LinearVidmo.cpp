//
// Created by viking on 24.10.20.
//


#include "../includes/LinearVidmo.h"

LinearVidmo::LinearVidmo(int numOfPoints): points(sf::Lines, numOfPoints) {}

void LinearVidmo::draw(const sf::RenderWindow& window) {
//    window.draw(points, sf::RenderStates());
    printf("draw\n");
}

void LinearVidmo::addPosition(sf::Vector2f possition) {
    points.append(sf::Vertex(possition));
}