/**
 * @file Paddle.hpp
 * @brief Contains the declaration of the Paddle class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

namespace Pong
{
	class Paddle : public sf::RectangleShape
	{
	public:
		Paddle();
	}; // class Paddle
} // namespace Pong

#endif