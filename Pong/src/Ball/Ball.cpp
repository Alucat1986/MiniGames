/**
 * @file Ball.cpp
 * @brief Contains the implementation of the Ball class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#include "Ball.hpp"
#include "../Utils/Constants.hpp"

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
	Ball::Ball() :
		sf::CircleShape(10.f)
	{
		setFillColor(sf::Color::White);
		setOrigin({ 10.f, 10.f });
		setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	} // Ball::Ball(...)
} // namespace Pong