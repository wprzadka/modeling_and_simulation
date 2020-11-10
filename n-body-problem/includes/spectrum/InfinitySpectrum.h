//
// Created by viking on 24.10.20.
//

#ifndef N_BODY_PROBLEM_INFINITYSPECTRUM_H
#define N_BODY_PROBLEM_INFINITYSPECTRUM_H


#include <SFML/Graphics.hpp>
#include "Spectrum.h"

class InfinitySpectrum : public Spectrum {
    sf::VertexArray points;

public:
    InfinitySpectrum();
    ~InfinitySpectrum() override = default;
    void draw (sf::RenderWindow& window) override;
    void addPosition(sf::Vector2f position) override;
};


#endif //N_BODY_PROBLEM_INFINITYSPECTRUM_H
