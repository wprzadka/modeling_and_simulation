//
// Created by viking on 09.11.2020.
//

#ifndef N_BODY_PROBLEM_GRID_H
#define N_BODY_PROBLEM_GRID_H


#include "../Body.h"

class Grid {

public:
    virtual void update(const std::vector<Body>&){};
    virtual void draw(sf::RenderWindow& window) = 0;
};


#endif //N_BODY_PROBLEM_GRID_H
