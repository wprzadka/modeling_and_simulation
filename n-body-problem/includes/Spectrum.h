//
// Created by viking on 24.10.20.
//

#ifndef N_BODY_PROBLEM_SPECTRUM_H
#define N_BODY_PROBLEM_SPECTRUM_H


class Spectrum {

public:
    virtual void draw (sf::RenderWindow& window) = 0;

    virtual void setColor(const sf::Color&) = 0;

    virtual void addPosition(sf::Vector2f position) = 0;
};


#endif //N_BODY_PROBLEM_SPECTRUM_H
