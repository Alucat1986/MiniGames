/**
 * @file Constants.hpp
 * @brief Contains some constants for the game.
 * @author Alunya
 * @date 14.05.2025
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdint>

namespace snake {
namespace constants {

/**
 * @defgroup GameGridInformationConstants Game Grid Information Constants
 * @brief Constants that define the size of a single cell and the amount of cells in x and y directions.
 * @author Alunya
 * @date 09.02.2025
 * @{
 */

/**
 * @brief The size of a cell, cells are squares.
 * @author Alunya
 * @date 09.02.2025
 */
constexpr float CELL_SIZE             = 64.0f;

/**
 * @brief The outline thickness of a cell.
 * @author Alunya
 * @date 14.05.2025
 */
constexpr float CELL_OUTLINETHICKNESS = 1.0f;

/**
 * @brief The amount of columns of cells.
 * @author Alunya
 * @date 14.05.2025
 */
constexpr std::size_t CELL_COLUMNS    = 20;

/**
 * @brief The amount of rows of cells.
 * @author Alunya
 * @date 14.05.2025
 */
constexpr std::size_t CELL_ROWS       = 10;

/**
 * @}
 */ // End of GameWindowConstants

/**
 * @defgroup GameWindowConstants Game Window Constants
 * @brief Constants that define the size of the game window.
 * @author Alunya
 * @date 04.01.2025
 * @{
 */

/**
 * @brief The margin of the game window.
 * @author Alunya
 * @date 14.05.2025
 *
 * The margin is used to center the grid in the window.
 */
constexpr float WINDOW_MARGIN         = 20.0f;

/**
 * @brief The width of the game window in pixels.
 * @author Alunya
 * @date 14.05.2025
 */
constexpr float WINDOW_WIDTH          = CELL_COLUMNS * CELL_SIZE + 2 * WINDOW_MARGIN;

/**
 * @brief The height of the game window in pixels.
 * @author Alunya
 * @date 14.05.2025
 */
constexpr float WINDOW_HEIGHT         = CELL_ROWS * CELL_SIZE + 2 * WINDOW_MARGIN;
;

/**
 * @}
 */ // End of GameWindowConstants

} // namespace constants
} // namespace snake

#endif // #ifndef CONSTANTS_HPP
