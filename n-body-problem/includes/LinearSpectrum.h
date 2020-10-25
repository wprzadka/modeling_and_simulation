//
// Created by viking on 24.10.20.
//

#ifndef N_BODY_PROBLEM_LINEAR_VIDMO_H
#define N_BODY_PROBLEM_LINEAR_VIDMO_H


#include <SFML/Graphics.hpp>
#include "Spectrum.h"

class LinearSpectrum : public Spectrum {
    sf::VertexArray points;

public:
    LinearSpectrum(int numOfPoints);

    void draw (const sf::RenderWindow& window);

    void addPosition(sf::Vector2f position);
};


#endif //N_BODY_PROBLEM_LINEAR_VIDMO_H
