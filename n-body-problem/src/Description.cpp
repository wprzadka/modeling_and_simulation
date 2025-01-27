//
// Created by viking on 14.11.20.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include <cmath>
#include "../includes/Description.h"
#include "../includes/Constants.h"

Description::Description()
        :font(),
         description(),
         triangleMarker(8, 3){
    if(font.loadFromFile("../font/FreeSans.otf")){
        description.setFont(font);
    }
    description.setCharacterSize(20);
}

Description::Description(const sf::Color& color)
        :font(),
        description(),
        triangleMarker(8, 3){
    if(font.loadFromFile("../font/FreeSans.otf")){
        description.setFont(font);
    }
    description.setCharacterSize(20);
    triangleMarker.setFillColor(color);
}

Description::Description(Description&& original) noexcept
    :font(original.font),
    description(std::move(original.description)),
    triangleMarker(std::move(original.triangleMarker)) {

    if(font.loadFromFile("../font/FreeSans.otf")){
        description.setFont(font);
    }
    description.setCharacterSize(20);
}

void Description::draw(sf::RenderWindow& window) {
    window.draw(description);
    if(isAsideFromWindow){
        window.draw(triangleMarker);
    }
}

void Description::update(
        const sf::Vector2f& position,
        const sf::Vector2<long double>& velocity,
        const sf::Vector2<long double>& acceleration,
        const double& mass,
        const sf::RenderWindow& window
        ) {

    std::ostringstream data;
    data.precision(0);
    data << std::scientific;
    data.precision(1);
    data << "velocity: "
         << sqrt(pow(velocity.x, 2) + pow(velocity.y, 2))
         << " [m/s]\n";
    data << "acceleration: "
        << sqrt(pow(acceleration.x, 2) + pow(acceleration.y, 2))
        << " [m/s^2]\n";
    data << "force: "
        << sqrt(pow(acceleration.x, 2) + pow(acceleration.y, 2) * pow(mass, 2))
        << " [N]\n";
//    data << "velocity: ("
//         << velocity.x << ", "
//         << velocity.y << ") [m/s]\n";
//    data << "acceleration: ("
//         << acceleration.x << ", "
//         << acceleration.y << ") [m/s^2]\n";
//    data << "force: ("
//         << acceleration.x * mass << ", "
//         << acceleration.y * mass << ") [N]\n";
    description.setString(data.str());

    float xPos = position.x;
    float yPos = position.y;
    float markerXPos = position.x;
    float markerYPos = position.y;
    isAsideFromWindow = false;

    float distance = 50;

    if(position.x < 0){
        markerXPos = distance;
        xPos = markerXPos + distance;
        triangleMarker.setRotation(-90);
        isAsideFromWindow = true;
    }else if(position.x > window.getSize().x){
        markerXPos = window.getSize().x - distance;
        xPos = markerXPos - distance;
        triangleMarker.setRotation(90);
        isAsideFromWindow = true;
    }
    if(position.y < 0){
        markerYPos = distance;
        yPos = markerYPos + distance;
        isAsideFromWindow = true;
    }else if(position.y > window.getSize().y){
        markerYPos = window.getSize().y - distance;
        yPos = markerYPos - distance;
        triangleMarker.setRotation(180);
        isAsideFromWindow = true;
    }

    if(isAsideFromWindow){
        isActive = true;
        triangleMarker.setPosition(markerXPos, markerYPos);
    }
    description.setPosition(xPos, yPos);
}
