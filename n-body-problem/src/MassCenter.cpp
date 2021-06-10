//
// Created by viking on 09.11.2020.
//

#include <cmath>
#include "../includes/MassCenter.h"
#include "../includes/Constants.h"


MassCenter::MassCenter(float size) : shape(size) {
    shape.setFillColor(sf::Color(0, 0, 0));
    shape.setOutlineColor(sf::Color(255, 255, 255));
    shape.setOutlineThickness((size + 1) / 2);
}

MassCenter::MassCenter(const std::vector<Body>& bodies, float size) : MassCenter(size) {
    calculateTotalMass(bodies);
    findMassCenter(bodies);
}

long double MassCenter::calculateTotalMass(const std::vector<Body>& bodies) {
    totalMassOfSystem = 0;
    for(const auto& body : bodies){
        totalMassOfSystem += body.getMass();
    }
    return totalMassOfSystem;
}

sf::Vector2<double> MassCenter::saveInitialMassCenter(const std::vector<Body>& bodies) {
    initialMassCenterPosition = findMassCenter(bodies);
    return initialMassCenterPosition;
}

sf::Vector2<double> MassCenter::getMassCenter(const std::vector<Body>& bodies) {
    findMassCenter(bodies);
    shape.setPosition(static_cast<sf::Vector2<float>>(massCenterPosition));
    sf::Vector2<double> dispVec = massCenterPosition - initialMassCenterPosition;
    displacement.emplace_back(std::sqrt(std::pow(dispVec.x, 2) + std::pow(dispVec.y, 2)) * DISTANCE_UNIT);
    return massCenterPosition;
}

sf::Vector2<double> MassCenter::findMassCenter(const std::vector<Body>& bodies) {
    massCenterPosition = sf::Vector2<double>{0, 0};
    for(const auto& body : bodies){
        massCenterPosition += body.getMass() * sf::Vector2<double>(body.getPosition());
    }
    if(totalMassOfSystem == 0){
        calculateTotalMass(bodies);
    }
    massCenterPosition /= static_cast<double>(totalMassOfSystem);
    return massCenterPosition;
}

void MassCenter::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}
