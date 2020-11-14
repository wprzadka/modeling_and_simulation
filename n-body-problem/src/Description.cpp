//
// Created by viking on 14.11.20.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include "../includes/Description.h"

Description::Description()
        :font(),
        description(){
    if(font.loadFromFile("../font/FreeSans.otf")){
        description.setFont(font);
    }
    description.setCharacterSize(20);
}

Description::Description(Description&& original)
    :font(original.font), description(std::move(original.description)) {
    if(font.loadFromFile("../font/FreeSans.otf")){
        description.setFont(font);
    }
    description.setCharacterSize(20);
}

void Description::draw(sf::RenderWindow& window) {
    window.draw(description);
}

void Description::update(
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        const sf::Vector2f& acceleration
        ) {

    std::ostringstream data;
    data.precision(0);
    data << std::fixed;
    data << "position: ("
         << position.x << ", "
         << position.y << ")\n";
    data.precision(1);
    data << "velocity: ("
         << velocity.x << ", "
         << velocity.y << ")\n";
    data << "force: "
         << acceleration.x << ", "
         << acceleration.y << ")";
    description.setString(data.str());
    description.setPosition(position.x, position.y);
}
