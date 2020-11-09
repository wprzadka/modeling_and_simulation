//
// Created by viking on 09.11.2020.
//

#include "../includes/MetricGrid.h"

MetricGrid::MetricGrid(std::pair<float, float> window_size, float distance, float thickness, sf::Color color)
    : lines(window_size.first + window_size.second / distance) {

    int width = static_cast<int>(window_size.first / distance);
    int height = static_cast<int>(window_size.second / distance);

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
}

void MetricGrid::draw(sf::RenderWindow & window) {
    for(const auto& rect : lines){
        window.draw(rect);
    }
}
