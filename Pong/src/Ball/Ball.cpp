/**
 * @file Ball.cpp
 * @brief Contains the implementation of the Ball class.
 * @author Alunya
 * @date 04.01.2025
 */

#include <cmath>
#include <iostream>
#include <numbers>
#include <random>

#include "Ball.hpp"

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
		m_Speed(400u),
		m_Direction({ 0, 0 })
	{
		setFillColor(sf::Color::White);
		setOrigin({ 10.f, 10.f });
		setRandomDirection();
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
		position.x += m_Direction.x * m_Speed * deltaTime;
		position.y += m_Direction.y * m_Speed * deltaTime;
		setPosition(position);
	} // void Ball::move(...)
	
	/**
	 * @brief Sets the speed of the ball.
	 * @param[in] speed The new speed the ball should have.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Ball::setSpeed(const std::uint16_t& speed)
	{
		m_Speed = speed;
	} // void Ball::setSpeed(...)
	
	/**
	 * @brief Returns the current speed of the ball.
	 * @return The balls' speed.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	std::uint16_t Ball::getSpeed() const
	{
		return m_Speed;
	} // std::uint16_t Ball::getSpeed(...)
	
	/**
	 * @brief Sets the direction in which the ball moves.
	 * @param[in] direction The new direction of the ball.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Ball::setDirection(const sf::Vector2f& direction)
	{
		m_Direction = direction;
	} // void Ball::setDirection(...)

	/**
	 * @brief Returns the balls' current direction.
	 * @return The current direction of the ball.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	sf::Vector2f Ball::getDirection() const
	{
		return m_Direction;
	} // sf::Vector2f Ball::getDirection(...)

	/**
	 * @brief Sets a random Direction for the Ball to start with.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Ball::setRandomDirection()
	{
		std::random_device random;
		std::mt19937 gen(random());
		std::uniform_real_distribution<float> distribution(0.f, 2.f * static_cast<float>(std::numbers::pi));

		float angle = distribution(gen);

		m_Direction.x = std::cos(angle);
		m_Direction.y = std::sin(angle);
	} // void Ball::setRandomDirection(...)
} // namespace Pong