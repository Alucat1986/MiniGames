/**
 * @file EnemyPaddle.cpp
 * @brief Contains the implementation of the EnemyPaddle class.
 * @author Alunya
 * @date 04.01.2025
 */

#include "EnemyPaddle.hpp"
#include "../Utils/Constants.hpp"

// ***************************************************************************************************************** //
//                                                                                                                   //
//                                                      CLASSES                                                      //
//                                                                                                                   //
// ***************************************************************************************************************** //

namespace Pong
{
	/**
	 * @brief Constructor.
	 * @author Alunya
	 * @date 04.01.2025
	 */
	EnemyPaddle::EnemyPaddle()
	{
		setFillColor(sf::Color::Red);
		setOrigin({ 10.f, 0.f });
		setPosition({ WINDOW_WIDTH - 10.f, 10.f });
	} // EnemyPaddle::EnemyPaddle(...)
} // namespace Pong