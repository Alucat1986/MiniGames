/**
 * @file Grid.cpp
 * @brief Contains the grid class implementation.
 * @author Alunya
 * @date 14.05.2025
 */

#include "Include/Grid/Grid.hpp"

#include "Include/Utils/Constants.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <cassert>
#include <cstdint>
#include <vector>

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      CLASSES                                                       //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace snake {

Grid::Grid() {
    mCells.reserve( constants::CELL_COLUMNS * constants::CELL_ROWS );
    createCells();
} // Grid::Grid(...)

void Grid::draw( sf::RenderWindow& window ) {
    for ( const auto& cell : mCells ) {
        window.draw( cell );
    }
} // void Grid::draw(...)

/**
 * @brief Converts a grid position to pixel coordinates.
 * @author Alunya
 * @date 25.05.2025
 * @param[in] position The grid position to convert.
 * @return sf::Vector2f The pixel coordinates.
 */
sf::Vector2f Grid::getCoordinates( const sf::Vector2f& position ) const {
    sf::Vector2f coordinates{ constants::WINDOW_MARGIN, constants::WINDOW_MARGIN };
    coordinates.x += position.x * constants::CELL_SIZE;
    coordinates.y += position.y * constants::CELL_SIZE;
    return coordinates;
} // sf::Vector2f Grid::getCoordinates(...) const

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
