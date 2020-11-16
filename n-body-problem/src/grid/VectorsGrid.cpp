//
// Created by viking on 10.11.2020.
//

#include <cmath>
#include "../../includes/grid/VectorsGrid.h"
#include "../../includes/Constants.h"

VectorsGrid::VectorsGrid(std::pair<float, float> window_size, float distance, sf::Color color, float multiplier)
    : unitDistance(distance), vertices(window_size.second / distance), color(color), forceMultiplier(multiplier){

        int width = static_cast<int>(window_size.first / unitDistance);
        int height = static_cast<int>(window_size.second / unitDistance);
        for(int y = 0; y < height; ++y){
            vertices[y].resize(window_size.first / unitDistance);
            for(int x = 0; x < width; ++x){
                vertices[y][x] = sf::Vertex{
                        sf::Vector2f{static_cast<float>(x), static_cast<float>(y)} * unitDistance, color
                };
            }
        }
}

void VectorsGrid::update(const std::vector<Body> & bodies) {
    for(int y = 0; y < vertices.size(); ++y){
        for(int x = 0; x < vertices[y].size(); ++x){
            sf::Vector2f position{x * unitDistance, y * unitDistance};
            sf::Vector2f changePosition{0, 0};
            for(const auto& body : bodies){

                sf::Vector2f diff = body.getPosition() - position; // [distance_units] -> vector

                float diff_sqrt = std::pow(diff.x, 2) + std::pow(diff.y, 2); // [distance_units^2]
                float norm_diff = std::sqrt(diff_sqrt); // [distance_units]

                sf::Vector2f diff_vec_normalized{diff.x / norm_diff, diff.y / norm_diff}; // [-] -> vector
                float distance_sqrt = diff_sqrt * std::pow(DISTANCE_UNIT, 2); // [m^2]

                sf::Vector2f curr_change = forceMultiplier * diff_vec_normalized * static_cast<float>(body.getMass())
                        * static_cast<float>(GRAVITATIONAL_CONST) /
                        distance_sqrt; // [kg^2⋅m^3⋅kg^−1⋅s^−2⋅m^-2] = [kg⋅m⋅s^-2] -> vector
                changePosition +=
                        (std::sqrt(std::pow(curr_change.x, 2) + std::pow(curr_change.y, 2)) < norm_diff
                         ? curr_change : diff);
            }
            vertices[y][x] = sf::Vertex{
                    position + changePosition,
                    color
            };
        }
    }
}

void VectorsGrid::draw(sf::RenderWindow &window) {
    for (int y = 0; y < vertices.size(); ++y) {
        for (int x = 0; x < vertices[y].size(); ++x) {
            sf::Vertex line[] =
                    {
                            vertices[y][x],
                            sf::Vector2f(x, y) * unitDistance
                    };
            window.draw(line, 2, sf::Lines);
        }
    }
}