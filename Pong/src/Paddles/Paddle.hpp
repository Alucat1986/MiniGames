/**
 * @file Paddle.hpp
 * @brief Contains the declaration of the Paddle class.
 * @author Alunya
 * @date 04.01.2025
 */

#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include <cstdint>

namespace Pong {
/**
 * @class Paddle
 * @brief Represents a basic paddle.
 * @author Alunya
 * @date 05.01.2025
 *
 * The Paddle class offers a basic functionality that every paddle in a pong
 * game should have.
 */
class Paddle : public sf::RectangleShape {
public:
    Paddle();

    virtual void move( const float& deltaTime );
    void         setSpeed( const uint16_t& speed );
    uint16_t     getSpeed() const;
    void         setDirection( const sf::Vector2i& direction );
    sf::Vector2i getDirection() const;

private:
    uint16_t     m_Speed;
    sf::Vector2i m_Direction;
}; // class Paddle

} // namespace Pong

#endif
