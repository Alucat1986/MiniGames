/**
 * @file Paddle.cpp
 * @brief Contains the implementation of the Paddle class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#include "Paddle.hpp"

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
	Paddle::Paddle() :
		sf::RectangleShape({ 10.f, 50.f }),
		m_Speed(50u),
		m_Direction({ 0, 0 })
	{
		setFillColor(sf::Color::White);
	} // Paddle::Paddle(...)

	/**
	 * @brief Moves the paddle in the current direction.
	 * @param[in] deltaTime const-reference to the time since the last frame in seconds.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	void Paddle::move(const float& deltaTime)
	{
		sf::Vector2f position = getPosition();
		position.y += m_Direction.y * m_Speed * deltaTime;
		setPosition(position);
	} // void Paddle::move(...)

	/**
	 * @brief Sets the speed of the paddle.
	 * @param[in] speed The new Speed of the paddle.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	void Paddle::setSpeed(const std::uint16_t& speed)
	{
		m_Speed = speed;
	} // void Paddle::setSpeed(...)

	/**
	 * @brief Returns the speed of the paddle.
	 * @return The speed of the paddle as std::uint16_t.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	std::uint16_t Paddle::getSpeed() const
	{
		return m_Speed;
	} // std::uint16_t Paddle::getSpeed(...)

	/**
	 * @brief Sets the direction of the paddle.
	 * @param[in] direction The new direction of the paddle as sf::Vector2i.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	void Paddle::setDirection(const sf::Vector2i& direction)
	{
		m_Direction = direction;
	} // void Paddle::setDirection(...)

	/**
	 * @brief Returns the direction of the paddle.
	 * @return The direction of the paddle as sf::Vector2i.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	sf::Vector2i Paddle::getDirection() const
	{
		return m_Direction;
	} // sf::Vector2i Paddle::getDirection(...)
} // namespace Pong