//
// Created by viking on 10.11.2020.
//

#include <cmath>
#include "../../includes/spectrum/ListSpectrum.h"

ListSpectrum::ListSpectrum(): Spectrum(), maxSize(200), points(std::make_unique<sf::Vertex[]>(200)) {
}

void ListSpectrum::draw(sf::RenderWindow &window) {

    window.draw(points.get(), size - 1, sf::LinesStrip);
}

void ListSpectrum::addPosition(sf::Vector2f position) {
    auto distanceFromLastVec = points[0].position - position;
    if(sqrt(pow(distanceFromLastVec.x, 2) + pow(distanceFromLastVec.y, 2)) < 1){
        return;
    }
    for(int i = size- 1; i > 0; --i){
        points[i] = points[i - 1];
        if(points[i].color.a > 0)
            --points[i].color.a;
    }
    points[0] = sf::Vertex(position, color);
    if(size < maxSize){
        ++size;
    }
}
