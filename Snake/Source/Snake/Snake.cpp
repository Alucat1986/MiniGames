/**
 * @file Snake.cpp
 * @brief Contains the snake class implementation.
 * @author Alunya
 * @date 16.05.2025
 */

#include "Include/Snake/Snake.hpp"

#include "Include/Graphics/AssetsManager.hpp"
#include "Include/Utils/Constants.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>

#include <iostream>
#include <iterator>
#include <list>
#include <memory>

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      CLASSES                                                       //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace snake {

/**
 * @brief Constructor.
 * @author Alunya
 * @date 16.05.2025
 */
Snake::Snake( const AssetsManager& assetsManager )
        : mDead( false ),
          mGrow( false ),
          mMoveTimeThreshold( 0.2f ),
          mCurrentTimeStamp( 0.0f ),
          mSnakeHeadSprite( std::make_unique<sf::Sprite>( assetsManager.getTexture( "SnakeHead" ) ) ),
          mSnakeBodySprite( std::make_unique<sf::Sprite>( assetsManager.getTexture( "SnakeBody" ) ) ),
          mSnakeTailSprite( std::make_unique<sf::Sprite>( assetsManager.getTexture( "SnakeTail" ) ) ) {
    mSnakeBody = std::make_unique<std::list<SnakePart>>();
    mSnakeBody->emplace_back( SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 1,
                                         .y         = constants::CELL_ROWS / 2,
                                         .direction = Direction::East,
                                         .part      = BodyPart::Tail } );
    mSnakeBody->emplace_back( SnakePart{ .x         = constants::CELL_COLUMNS / 2,
                                         .y         = constants::CELL_ROWS / 2,
                                         .direction = Direction::East,
                                         .part      = BodyPart::Head } );

    mSnakeHeadSprite->setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );
    mSnakeBodySprite->setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );
    mSnakeTailSprite->setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    sf::Angle rotation = sf::degrees( -90.0f );
    mSnakeHeadSprite->rotate( rotation );
    mSnakeBodySprite->rotate( rotation );
    mSnakeTailSprite->rotate( rotation );
} // Snake::Snake(...)

/**
 * @brief Updates the snakes state.
 * @author Alunya
 * @date 16.05.2025
 * @param[in] deltaTime The time that has passed since the last update had been called.
 *
 * Is called by Game::update(). It moves the snake into the current direction by a cell and then checks if it collides
 * with food, itself or a wall to then either grow in size or die. The deltatime parameter is used to check against the
 * m_MoveTimestamp if it's time to move the snake, default behaviour is that every 0.2ms the snake will move one grid
 * cell into the set current direction.
 */
void Snake::update( const float& deltaTime ) {
    mCurrentTimeStamp += deltaTime;
    /** @todo Either before or after moving find out if we collide or might collide with something and do the
     * corresponding action, aka grow, die or just move. */
    if ( mCurrentTimeStamp >= mMoveTimeThreshold ) {
        move();
        mCurrentTimeStamp -= mMoveTimeThreshold;
    } // if ( mCurrentTimeStamp >= mMoveTimeThreshold )
} // Snake::update(...)

/**
 * @brief To check if the snake is dead or alive.
 * @author Alunya
 * @date 14.05.2025
 *
 * @return true When the snake is dead.
 * @return false When the snake is alive.
 */
bool Snake::isDead() const {
    return mDead;
}

/**
 * @brief Moves the snake into the current direction.
 * @author Alunya
 * @date 16.05.2025
 *
 * Movement starts from the tail, when the grow flag is set the tail will be skipped to put a new body part right
 * infront of the tail.
 */
void Snake::move() {
    std::list<SnakePart>::iterator snakeIterator = mSnakeBody->begin();
    if ( mGrow ) {
        std::advance( snakeIterator, 1 ); // Should never be mSnakeBody->end(), otherwise something went wrong.
        mSnakeBody->emplace( snakeIterator, SnakePart{ .x         = snakeIterator->x,
                                                       .y         = snakeIterator->y,
                                                       .direction = snakeIterator->direction,
                                                       .part      = BodyPart::Body } );
        mGrow = false;
    } // if ( mGrow )

    for ( ; snakeIterator != mSnakeBody->end(); std::advance( snakeIterator, 1 ) ) {
        switch ( snakeIterator->direction ) {
            case Direction::North :
                snakeIterator->y--;
                break;
            case Direction::East :
                snakeIterator->x++;
                break;
            case Direction::South :
                snakeIterator->y++;
                break;
            case Direction::West :
                snakeIterator->x--;
                break;
        } // switch ( SnakeIterator->Direction )

        if ( snakeIterator->part == BodyPart::Head ) {
            break;
        } // if ( SnakeIterator->part == BodyPart::Head )

        snakeIterator->direction = std::next( snakeIterator )->direction;
    } // for ( ; SnakeIterator != mSnakeBody->end(); std::next( SnakeIterator ) )
} // Snake::move(...)

/**
 * @brief Grows the snake by 1 cell.
 * @author Alunya
 * @date 16.05.2025
 */
void Snake::grow() {
    // Probably unnecessary as when the snake reaches it's max length it's about to die anyway.
    if ( mSnakeBody->size() < constants::MAX_SNAKE_LENGTH ) {
        mGrow = true;
    } // if ( mSnakeBody->size() < constants::MAX_SNAKE_LENGTH)
} // Snake::grow(...)

/**
 * @brief Kills the snake.
 * @author Alunya
 * @date 16.05.2025
 */
void Snake::die() {
    mDead = true;
} // Snake::die(...)

} // namespace snake
