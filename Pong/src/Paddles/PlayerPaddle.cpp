/**
 * @file PlayerPaddle.cpp
 * @brief Contains the implementation of the PlayerPaddle class.
 * @author Alunya
 * @date 04.01.2025
 */

#include "PlayerPaddle.hpp"

#include <SFML/Graphics/Color.hpp>

// ***************************************************************************************************************** //
//                                                                                                                   //
//                                                      CLASSES                                                      //
//                                                                                                                   //
// ***************************************************************************************************************** //

namespace Pong {
/**
 * @brief Constructor.
 * @author Alunya
 * @date 04.01.2025
 */
PlayerPaddle::PlayerPaddle() {
    setFillColor( sf::Color::Green );
} // PlayerPaddle::PlayerPaddle(...)

} // namespace Pong
