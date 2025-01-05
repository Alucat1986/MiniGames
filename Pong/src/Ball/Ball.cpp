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

	/**
	 * @brief Moves the Ball in the set Direction.
	 * @param[in] deltaTime The time that has passed since the last frame.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Ball::move(const float& deltaTime)
	{
		sf::Vector2f position = getPosition();
		position.y += m_Direction.y * m_Speed * deltaTime;
		setPosition(position);
	}
	
	/**
	 * @brief Sets the speed of the ball.
	 * @param[in] speed The new speed the ball should have.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Ball::setSpeed(const std::uint16_t& speed)
	{
		m_Speed = speed;
	}
	
	/**
	 * @brief Returns the current speed of the ball.
	 * @return The balls' speed.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	std::uint16_t Ball::getSpeed() const
	{
		return m_Speed;
	}
	
	/**
	 * @brief Sets the direction in which the ball moves.
	 * @param[in] direction The new direction of the ball.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Ball::setDirection(const sf::Vector2f& direction)
	{
		m_Direction = direction;
	}

	/**
	 * @brief Returns the balls' current direction.
	 * @return The current direction of the ball.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	sf::Vector2f Ball::getDirection() const
	{
		return m_Direction;
	}
} // namespace Pong