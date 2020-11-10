//
// Created by viking on 09.11.2020.
//

#include <sstream>
#include "../../includes/grid/MetricGrid.h"
#include "SFML/System.hpp"

MetricGrid::MetricGrid(std::pair<float, float> window_size, float distance, sf::Color color, float thickness)
    : lines(window_size.first + window_size.second / distance), font(), distancePerTile(){

    int width = static_cast<int>(window_size.first / distance);
    int height = static_cast<int>(window_size.second / distance);

    // initialize grid lines
    sf::Vector2f vertical{thickness, window_size.second};
    for (int x = 0; x < width; ++x) {
        lines[x] = sf::RectangleShape(vertical);
        lines[x].setPosition(x * distance, 0);
    }
    sf::Vector2f horizontal{window_size.first, thickness};
    for (int y = 0; y < height; ++y) {
        lines[y + width] = sf::RectangleShape(horizontal);
        lines[y + width].setPosition(0, y * distance);
    }
    for (auto &line : lines) {
        line.setFillColor(color);
    }
    // initialize description of distance unit
    if(font.loadFromFile("../font/FreeSans.otf")){
        distancePerTile.setFont(font);
    }
    distancePerTile.setCharacterSize(18);
    std::ostringstream unitAsText;
    unitAsText << distance * DISTANCE_UNIT;
    distancePerTile.setString("1 unit = " + unitAsText.str() + " [m]");
    distancePerTile.setPosition(distance / 4, distance / 4);
}

void MetricGrid::draw(sf::RenderWindow & window) {
    for(const auto& rect : lines){
        window.draw(rect);
    }
    window.draw(distancePerTile);
}
