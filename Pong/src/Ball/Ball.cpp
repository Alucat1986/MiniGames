/**
 * @file Ball.cpp
 * @brief Contains the implementation of the Ball class.
 * @author Alunya
 * @date 04.01.2025
 */

#include "Ball.hpp"
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
	Ball::Ball() :
		sf::CircleShape(10.f),
		m_Speed(50u),
		m_Direction({ 0, 0 })
	{
		setFillColor(sf::Color::White);
		setOrigin({ 10.f, 10.f });
		setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	} // Ball::Ball(...)
} // namespace Pong