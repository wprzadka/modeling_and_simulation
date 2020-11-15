//
// Created by viking on 14.11.20.
//

#ifndef N_BODY_PROBLEM_DESCRIPTION_H
#define N_BODY_PROBLEM_DESCRIPTION_H

#include <SFML/Graphics.hpp>

class Description {
    sf::Font font;
    sf::Text description;
    sf::CircleShape triangleMarker;

public:
    bool isActive = false;
    bool isAsideFromWindow = false;

    Description();
    Description(const sf::Color&);
    Description(Description&&) noexcept;

    void draw(sf::RenderWindow& window);
    void update(
            const sf::Vector2f& position,
            const sf::Vector2<long double>& velocity,
            const sf::Vector2<long double>& acceleration,
            const double& mass,
            const sf::RenderWindow& window
            );
};


#endif //N_BODY_PROBLEM_DESCRIPTION_H
