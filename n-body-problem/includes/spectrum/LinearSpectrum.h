//
// Created by viking on 24.10.20.
//

#ifndef N_BODY_PROBLEM_LINEAR_VIDMO_H
#define N_BODY_PROBLEM_LINEAR_VIDMO_H


#include <SFML/Graphics.hpp>
#include "Spectrum.h"

class LinearSpectrum : public Spectrum {
    sf::VertexArray points;
    sf::Color color;

public:
    LinearSpectrum();
    ~LinearSpectrum() override = default;
    void draw (sf::RenderWindow& window) override;
    void setColor(const sf::Color&) override;
    void addPosition(sf::Vector2f position) override;
};


#endif //N_BODY_PROBLEM_LINEAR_VIDMO_H
