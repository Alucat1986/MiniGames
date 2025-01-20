/**
 * @file Ball.hpp
 * @brief Contains the declaration of the Ball class.
 * @author Alunya
 * @date 04.01.2025
 */

#ifndef BALL_HPP
#define BALL_HPP

#include <cstdint>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace Pong {
	/**
	 * @class Ball
	 * @brief It defines the Ball of the game.
	 * @author Alunya
	 * @date 05.01.2025
	 *
	 * The Ball class inherits from the SFML CircleShape for it's drawability as
	 * well as it's movability. Plus a ball is obviously round in shape.
	 */
	class Ball : public sf::CircleShape {
	public:
								Ball();

		void					move( const float& deltaTime );
		void					setSpeed( const std::uint16_t& speed );
		std::uint16_t			getSpeed() const;
		void					setDirection( const sf::Vector2f& direction );
		sf::Vector2f			getDirection() const;
		void					setRandomDirection();

	private:
		std::uint16_t			m_Speed;
		sf::Vector2f			m_Direction;
	}; // class Ball
} // namespace Pong

#endif