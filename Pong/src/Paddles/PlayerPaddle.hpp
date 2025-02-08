/**
 * @file PlayerPaddle.hpp
 * @brief Contains the declaration of the PlayerPaddle class.
 * @author Alunya
 * @date 04.01.2025
 */

#ifndef PLAYERPADDLE_HPP
#define PLAYERPADDLE_HPP

#include "Paddle.hpp"

namespace Pong {
/**
 * @class PlayerPaddle
 * @brief Represents the paddle controlled by the player.
 * @author Alunya
 * @date 04.01.2025
 *
 * The PlayerPaddle class inherits from the Paddle class and adds functionality
 * specific to the player's paddle, such as initialization of it's appearance
 * and position.
 */
class PlayerPaddle : public Paddle {
public:
    PlayerPaddle();
}; // class PlayerPaddle

} // namespace Pong

#endif
