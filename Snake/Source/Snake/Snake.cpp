/**
 * @file Snake.cpp
 * @brief Contains the snake class implementation.
 * @author Alunya
 * @date 31.05.2025
 */

#include "Include/Snake/Snake.hpp"

#include "Include/Graphics/AssetsManager.hpp"
#include "Include/Grid/Grid.hpp"
#include "Include/Utils/Constants.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>

#include <iostream>
#include <iterator>
#include <list>
#include <memory>

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      PUBLIC                                                        //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace snake {

/**
 * @brief Constructor.
 * @author Alunya
 * @date 31.05.2025
 */
Snake::Snake( const AssetsManager& assetsManager )
        : mDead( false ),
          mGrow( false ),
          mMoveTimeThreshold( 0.3f ),
          mCurrentTimeStamp( 0.0f ),
          mAssetsManager( assetsManager ),
          mSnakeBody( std::make_unique<std::list<SnakePart>>() ) {
    mSnakeBody->emplace_back( SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 4,
                                         .y         = constants::CELL_ROWS / 2,
                                         .direction = Direction::East,
                                         .part      = BodyPart::Tail,
                                         .sprite    = sf::Sprite( mAssetsManager.getTexture( "SnakeTail" ) ) } );
    mSnakeBody->back().sprite.setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    mSnakeBody->emplace_back( SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 3,
                                         .y         = constants::CELL_ROWS / 2,
                                         .direction = Direction::East,
                                         .part      = BodyPart::Mid,
                                         .sprite    = sf::Sprite( mAssetsManager.getTexture( "SnakeMid" ) ) } );
    mSnakeBody->back().sprite.setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    mSnakeBody->emplace_back( SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 2,
                                         .y         = constants::CELL_ROWS / 2,
                                         .direction = Direction::East,
                                         .part      = BodyPart::Mid,
                                         .sprite    = sf::Sprite( mAssetsManager.getTexture( "SnakeMid" ) ) } );
    mSnakeBody->back().sprite.setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    mSnakeBody->emplace_back( SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 1,
                                         .y         = constants::CELL_ROWS / 2,
                                         .direction = Direction::East,
                                         .part      = BodyPart::Mid,
                                         .sprite    = sf::Sprite( mAssetsManager.getTexture( "SnakeMid" ) ) } );
    mSnakeBody->back().sprite.setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    mSnakeBody->emplace_back( SnakePart{ .x         = constants::CELL_COLUMNS / 2,
                                         .y         = constants::CELL_ROWS / 2,
                                         .direction = Direction::East,
                                         .part      = BodyPart::Head,
                                         .sprite    = sf::Sprite( mAssetsManager.getTexture( "SnakeHead" ) ) } );
    mSnakeBody->back().sprite.setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    rotateBodySprites();
} // Snake::Snake(...)

/**
 * @brief Updates the snakes state.
 * @author Alunya
 * @date 31.05.2025
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
        rotateBodySprites();
        mCurrentTimeStamp -= mMoveTimeThreshold;
    } // if ( mCurrentTimeStamp >= mMoveTimeThreshold )
} // Snake::update(...)

/**
 * @brief Draws the snake on the given render window.
 * @author Alunya
 * @date 31.05.2025
 * @param[in] window The render window to draw the snake on.
 */
void Snake::draw( sf::RenderWindow& window, const Grid& grid ) const {
    for ( auto& bodyPart : *mSnakeBody ) {
        switch ( bodyPart.part ) {
            case BodyPart::Head:
                bodyPart.sprite.setPosition(
                    grid.getCoordinates( { static_cast<float>( bodyPart.x ), static_cast<float>( bodyPart.y ) } ) );
                break;
            case BodyPart::Mid:
                bodyPart.sprite.setPosition(
                    grid.getCoordinates( { static_cast<float>( bodyPart.x ), static_cast<float>( bodyPart.y ) } ) );
                break;
            case BodyPart::Tail:
                bodyPart.sprite.setPosition(
                    grid.getCoordinates( { static_cast<float>( bodyPart.x ), static_cast<float>( bodyPart.y ) } ) );
                break;
        } // switch ( bodyPart.part )
        window.draw( bodyPart.sprite );
    } // for ( const auto& bodyPart : *mSnakeBody )
} // void draw(...) const

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
 * @brief Sets the direction of the snake.
 * @author Alunya
 * @date 31.05.2025
 * @param[in] newDirection The new direction to set.
 */
void Snake::setDirection( Direction newDirection ) {
    // front(): tail, back(): head
    mSnakeBody->back().direction = newDirection;
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
        mSnakeBody->emplace( snakeIterator,
                             SnakePart{ .x         = snakeIterator->x,
                                        .y         = snakeIterator->y,
                                        .direction = snakeIterator->direction,
                                        .part      = BodyPart::Mid,
                                        .sprite    = sf::Sprite( mAssetsManager.getTexture( "SnakeMid" ) ) } );
        mGrow = false;
    } // if ( mGrow )

    for ( ; snakeIterator != mSnakeBody->end(); std::advance( snakeIterator, 1 ) ) {
        switch ( snakeIterator->direction ) {
            case Direction::North:
                snakeIterator->y--;
                break;
            case Direction::East:
                snakeIterator->x++;
                break;
            case Direction::South:
                snakeIterator->y++;
                break;
            case Direction::West:
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

/**
 * @brief Rotates the body part sprites to face the current direction.
 * @author Alunya
 * @date 31.05.2025
 */
void Snake::rotateBodySprites() {
    sf::Angle rotation = sf::degrees( 0.0f );
    for ( auto& bodyPart : *mSnakeBody ) {
        switch ( bodyPart.direction ) {
            case Direction::North:
                bodyPart.sprite.setRotation( rotation - sf::degrees( 180.0f ) );
                bodyPart.sprite.setOrigin( { constants::CELL_SIZE, constants::CELL_SIZE } );
                break;
            case Direction::East:
                bodyPart.sprite.setRotation( rotation - sf::degrees( 90.0f ) );
                bodyPart.sprite.setOrigin( { constants::CELL_SIZE, 0.0f } );
                break;
            case Direction::South:
                bodyPart.sprite.setRotation( rotation );
                bodyPart.sprite.setOrigin( { 0.0f, 0.0f } );
                break;
            case Direction::West:
                bodyPart.sprite.setRotation( rotation + sf::degrees( 90.0f ) );
                bodyPart.sprite.setOrigin( { 0.0f, constants::CELL_SIZE } );
                break;
        } // switch ( bodyPart.direction )
    }
} // void Snake::rotateBodySprites(...)

} // namespace snake
