//
// Created by viking on 14.11.20.
//

#ifndef N_BODY_PROBLEM_DESCRIPTION_H
#define N_BODY_PROBLEM_DESCRIPTION_H

#include <SFML/Graphics.hpp>

class Description {
    sf::Vector2f descriptionPosition;
    bool isActive = false;

    sf::Font font;
    sf::Text description;

public:
    Description();
    Description(Description&&);

    void draw(sf::RenderWindow& window);
    void update(
            const sf::Vector2f& position,
            const sf::Vector2f& velocity,
            const sf::Vector2f& acceleration
            );
};


#endif //N_BODY_PROBLEM_DESCRIPTION_H
