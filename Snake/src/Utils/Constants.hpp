/**
 * @file Constants.hpp
 * @brief Contains some constants for the game.
 * @author Alunya
 * @date 09.02.2025
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

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
constexpr float CELL_SIZE            = 64.0f;

/**
 * @brief The margin of a cell.
 * @author Alunya
 * @date 09.02.2025
 */
constexpr float CELL_MARGIN          = 1.0f;

/**
 * @brief The amount of columns of cells.
 * @author Alunya
 * @date 09.02.2025
 */
constexpr std::uint16_t CELL_COLUMNS = 20;

/**
 * @brief The amount of rows of cells.
 * @author Alunya
 * @date 09.02.2025
 */
constexpr std::uint16_t CELL_ROWS    = 10;

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
 * @brief The width of the game window in pixels.
 * @author Alunya
 * @date 04.01.2025
 */
constexpr float WINDOW_WIDTH         = 800.0f;

/**
 * @brief The height of the game window in pixels.
 * @author Alunya
 * @date 04.01.2025
 */
constexpr float WINDOW_HEIGHT        = 600.0f;

/**
 * @}
 */ // End of GameWindowConstants

#endif
