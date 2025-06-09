/**
 * @file Grid.cpp
 * @brief Contains the grid class implementation.
 * @author Alunya
 * @date 31.05.2025
 */

#include "Include/Grid/Grid.hpp"

#include "Include/Utils/Constants.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <cassert>
#include <cstdint>
#include <memory>
#include <vector>

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      PUBLIC                                                        //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace snake {

/**
 * @brief Constructor.
 * @author Alunya
 * @date 31.05.2025
 */
Grid::Grid()
        : mGameField( std::make_unique<sf::RectangleShape>( sf::Vector2f{
              constants::CELL_COLUMNS * constants::CELL_SIZE, constants::CELL_ROWS * constants::CELL_SIZE } ) ) {
    mGameField->setPosition( { constants::WINDOW_MARGIN, constants::WINDOW_MARGIN } );
    mGameField->setOutlineColor( sf::Color::White );
    mGameField->setOutlineThickness( constants::CELL_OUTLINETHICKNESS * 2.0f );
    mGameField->setFillColor( sf::Color::Black );
    mCells.reserve( constants::CELL_COLUMNS * constants::CELL_ROWS );
    createCells();
} // Grid::Grid(...)

/**
 * @brief Draws the grid to the specified window.
 * @author Alunya
 * @date 31.05.2025
 * @param[in] window The window to draw the grid on.
 */
void Grid::draw( sf::RenderWindow& window, bool drawGrid ) const {
    window.draw( *mGameField );
    if ( drawGrid ) {
        for ( const auto& cell : mCells ) {
            window.draw( cell );
        } // for ( const auto& cell : mCells )
    } // if ( drawGrid )
} // void Grid::draw(...)

/**
 * @brief Converts a grid position to pixel coordinates.
 * @author Alunya
 * @date 31.05.2025
 * @param[in] cellCoordinates The grid position to convert.
 * @return sf::Vector2f The pixel coordinates.
 */
sf::Vector2f Grid::getCoordinates( const sf::Vector2f& cellCoordinates ) const {
    sf::Vector2f coordinates{ constants::WINDOW_MARGIN, constants::WINDOW_MARGIN };
    coordinates.x += cellCoordinates.x * constants::CELL_SIZE;
    coordinates.y += cellCoordinates.y * constants::CELL_SIZE;
    return coordinates;
} // sf::Vector2f Grid::getCoordinates(...) const

/**
 * @brief Checks if a cell is within the game field.
 * @author Alunya
 * @date 31.05.2025
 * @param[in] cellCoordinates The cell to check.
 * @return true If the cell is within the game field, otherwise false.
 */
bool Grid::isCellInGameField( const sf::Vector2f& cellCoordinates ) const {
    return cellCoordinates.x >= 0 && cellCoordinates.x <= constants::CELL_COLUMNS && cellCoordinates.y >= 0 &&
           cellCoordinates.y <= constants::CELL_ROWS;
} // bool Grid::isCellInGameField(...)

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      PRIVATE                                                       //
//                                                                                                                    //
// ****************************************************************************************************************** //

/**
 * @brief Creates the cells for the grid.
 * @author Alunya
 * @date 25.05.2025
 *
 * This function initializes the grid cells with their size, position, fill color, outline color, and outline thickness.
 */
void Grid::createCells() {
    sf::Vector2f cellSize( { constants::CELL_SIZE, constants::CELL_SIZE } );
    for ( std::size_t row{ 0 }; row < constants::CELL_ROWS; row++ ) {
        for ( std::size_t column{ 0 }; column < constants::CELL_COLUMNS; column++ ) {
            mCells.emplace_back( cellSize );
            mCells.back().setPosition( { constants::WINDOW_MARGIN + column * constants::CELL_SIZE,
                                         constants::WINDOW_MARGIN + row * constants::CELL_SIZE } );
            mCells.back().setFillColor( sf::Color::Black );
            mCells.back().setOutlineColor( sf::Color::White );
            mCells.back().setOutlineThickness( constants::CELL_OUTLINETHICKNESS );
        } // for ( std::uint16_t column{ 0 }; column < constants::CELL_COLUMNS;  column++ )
    } // for ( std::uint16_t row = 0; row < constants::CELL_ROWS; row++ )

    assert( mCells.size() == constants::CELL_COLUMNS * constants::CELL_ROWS );
} // void Grid::createCells(...)

} // namespace snake
