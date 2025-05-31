/**
 * @file Snake.hpp
 * @brief Contains the snake class declaration.
 * @author Alunya
 * @date 25.05.2025
 */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Include/Graphics/AssetsManager.hpp"
#include "Include/Grid/Grid.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <list>
#include <memory>

namespace snake {

using std::size_t;

/**
 * @class Snake
 * @brief Manages the snake, provides methods to grow the snake and move it.
 * @author Alunya
 * @date 25.05.2025
 *
 * The snake class represents the players snake. It provides following functionality:
 * * moving
 * * growing, after eating food
 * * dying
 * The movement is given by the players input and happens in a grid system, it will move one cell into the desired
 * direction. The snake can't stop so even when the player stops holding down a key the snake keeps going into the last
 * known direction the player wanted until a new command is received. When the snake eats food, collides with the
 * corresponding entity, it will grow a new mid part, so over time it will be harder for the player to evade its own
 * size. As soon as the snake collides with itself or the walls the snake dies. All those "systems" though will be
 * called by it's own update function as that will ask the grid class if it's colliding with something and act
 * accordingly. The snake will start with a length of 2, which is only the head and the tail of it. Each food item will
 * grow it by 1 cell. It also starts facing/moving east.
 */
class Snake {
public:
    enum class Direction {
        North,
        East,
        South,
        West
    };

public:
    Snake( const AssetsManager& assetsManager );
    ~Snake() = default;

    void update( const float& deltaTime );
    void draw( sf::RenderWindow& window, const Grid& grid ) const;
    bool isDead() const;
    void setDirection( Direction newDirection );

private:
    void move();
    void grow();
    void die();

private:
    enum class BodyPart {
        Head,
        Mid,
        Tail
    };

    struct SnakePart {
        size_t    x;
        size_t    y;
        Direction direction;
        BodyPart  part;
    };

    bool  mDead;
    bool  mGrow;
    float mMoveTimeThreshold; // every m_MoveTimeThreshold milliseconds the snake moves 1 cell.
    float mCurrentTimeStamp;  // the current time since the last move.

    std::unique_ptr<std::list<SnakePart>> mSnakeBody;
    std::unique_ptr<sf::Sprite>           mSnakeHeadSprite;
    std::unique_ptr<sf::Sprite>           mSnakeMidSprite;
    std::unique_ptr<sf::Sprite>           mSnakeTailSprite;
}; // class Snake

} // namespace snake

#endif // #ifndef SNAKE_HPP
