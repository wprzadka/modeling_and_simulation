//
// Created by viking on 24.10.20.
//

#ifndef N_BODY_PROBLEM_VIDMO_H
#define N_BODY_PROBLEM_VIDMO_H


class Vidmo {

public:
    virtual void draw (const sf::RenderWindow& window) = 0;

    virtual void addPosition(sf::Vector2f position) = 0;
};


#endif //N_BODY_PROBLEM_VIDMO_H
