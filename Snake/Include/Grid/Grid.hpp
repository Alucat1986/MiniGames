/**
 * @file Grid.hpp
 * @brief Contains the grid class declaration.
 * @author Alunya
 * @date 25.05.2025
 */

#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

namespace snake {

/**
 * @class Grid
 * @brief Manages the grid system for the game.
 * @author Alunya
 * @date 25.05.2025
 *
 * The grid class is responsible for managing the grid system used in the game.
 * It provides methods to draw the grid and handle cell-related operations.
 */
class Grid {
public:
    Grid();

    void         draw( sf::RenderWindow& window );
    sf::Vector2f getCoordinates( const sf::Vector2f& position ) const;

private:
    void createCells();

private:
    std::vector<sf::RectangleShape> mCells;
};

} // namespace snake

#endif // #ifndef GRID_HPP
