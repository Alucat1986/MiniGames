/**
 * @file PlayerPaddle.cpp
 * @brief Contains the implementation of the PlayerPaddle class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#include "PlayerPaddle.hpp"

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                     FUNCTIONS                                                      //
//                                                                                                                    //
// ****************************************************************************************************************** //

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      CLASSES                                                       //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace Pong
{
	/**
	 * @brief Constructor.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	PlayerPaddle::PlayerPaddle()
	{
		setFillColor(sf::Color::Green);
		setPosition({ 10.f, 10.f });
	} // PlayerPaddle::PlayerPaddle(...)
} // namespace Pong