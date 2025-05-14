#ifndef GRID_HPP
#define GRID_HPP

#include "Utils/Constants.hpp"

#include <SFML/Graphics.hpp>

class Grid {
public:
    Grid();
    void draw( sf::RenderWindow& window );

private:
    sf::RectangleShape cellShape;
};

#endif // GRID_HPP
