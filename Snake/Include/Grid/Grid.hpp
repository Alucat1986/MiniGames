/**
 * @file Grid.hpp
 * @brief Contains the grid class declaration.
 * @author Alunya
 * @date 14.05.2025
 */

#ifndef GRID_HPP
#define GRID_HPP

#include "Include/Utils/Constants.hpp"

#include <SFML/Graphics.hpp>

namespace snake {

/**
 * @class Grid
 * @brief Manages the grid system for the game.
 * @author Alunya
 * @date 14.05.2025
 *
 * The grid class is responsible for managing the grid system used in the game.
 * It provides methods to draw the grid and handle cell-related operations.
 */
class Grid {
public:
    Grid();
    void draw( sf::RenderWindow& window );

private:
    sf::RectangleShape mCellShape;
};

} // namespace snake

#endif // #ifndef GRID_HPP
