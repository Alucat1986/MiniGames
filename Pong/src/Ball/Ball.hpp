/**
 * @file Ball.hpp
 * @brief Contains the declaration of the Ball class.
 * @author Alunya
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

	private:
		std::uint16_t	m_Speed;
		sf::Vector2i	m_Direction;
	}; // class Ball
} // namespace Pong

#endif