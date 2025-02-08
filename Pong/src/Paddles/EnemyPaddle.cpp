/**
 * @file EnemyPaddle.cpp
 * @brief Contains the implementation of the EnemyPaddle class.
 * @author Alunya
 * @date 04.01.2025
 */

#include "EnemyPaddle.hpp"

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
EnemyPaddle::EnemyPaddle() {
    setSpeed( 200u );
    setFillColor( sf::Color::Red );
    setOrigin( { 10.0f, 0.0f } );
} // EnemyPaddle::EnemyPaddle(...)

} // namespace Pong
