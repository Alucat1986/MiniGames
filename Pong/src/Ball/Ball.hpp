/**
 * @file Ball.hpp
 * @brief Contains the declaration of the Ball class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics/CircleShape.hpp>

namespace Pong
{
	class Ball : public sf::CircleShape
	{
	public:
		Ball();
	}; // class Ball
} // namespace Pong

#endif