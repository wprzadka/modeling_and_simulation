//
// Created by viking on 10.11.2020.
//

#ifndef N_BODY_PROBLEM_LISTSPECTRUM_H
#define N_BODY_PROBLEM_LISTSPECTRUM_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "Spectrum.h"

class ListSpectrum : public Spectrum{
    std::unique_ptr<sf::Vertex[]> points;
    int maxSize = 0;
    int size = 0;

public:
    ListSpectrum();
    ~ListSpectrum() override = default;
    void draw (sf::RenderWindow& window) override;
    void addPosition(sf::Vector2f position) override;
};


#endif //N_BODY_PROBLEM_LISTSPECTRUM_H
